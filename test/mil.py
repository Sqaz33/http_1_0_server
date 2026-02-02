import asyncio
import aiohttp
from datetime import datetime
import sys

async def make_request(session, url, request_id):
    """Отправляет запрос и возвращает результат с ошибкой если есть"""
    try:
        async with session.get(url) as response:
            # Читаем ответ полностью
            body = await response.read()
            return {
                'id': request_id,
                'status': response.status,
                'success': True,
                'body_length': len(body),
                'error': None
            }
    except aiohttp.ClientConnectionError as e:
        return {
            'id': request_id,
            'status': None,
            'success': False,
            'body_length': 0,
            'error': f'ConnectionError: {e}'
        }
    except aiohttp.ClientResponseError as e:
        return {
            'id': request_id,
            'status': e.status,
            'success': False,
            'body_length': 0,
            'error': f'ResponseError ({e.status}): {e}'
        }
    except asyncio.TimeoutError:
        return {
            'id': request_id,
            'status': None,
            'success': False,
            'body_length': 0,
            'error': 'Timeout'
        }
    except Exception as e:
        return {
            'id': request_id,
            'status': None,
            'success': False,
            'body_length': 0,
            'error': f'Unexpected: {type(e).__name__}: {e}'
        }

async def test_single_request(url):
    """Отправляет один запрос и выводит подробную диагностику"""
    print("=" * 60)
    print("🔄 ТЕСТОВЫЙ ЗАПРОС - ДИАГНОСТИКА")
    print("=" * 60)
    
    connector = aiohttp.TCPConnector(ssl=False, force_close=True)
    timeout = aiohttp.ClientTimeout(total=10, connect=5, sock_read=5)
    
    async with aiohttp.ClientSession(
        connector=connector, 
        timeout=timeout,
        raise_for_status=False  # Не выбрасывать исключение при ошибках HTTP
    ) as session:
        try:
            print(f"Пытаюсь подключиться к: {url}")
            print(f"Таймаут: {timeout.total} секунд")
            
            start_time = datetime.now()
            async with session.get(url) as response:
                elapsed = (datetime.now() - start_time).total_seconds()
                
                print(f"\n✅ Подключение установлено за {elapsed:.2f} сек")
                print(f"📊 Статус HTTP: {response.status} {response.reason}")
                
                # Заголовки
                print(f"\n📨 Заголовки ответа ({len(response.headers)}):")
                for header, value in response.headers.items():
                    print(f"  {header}: {value}")
                
                # Пытаемся прочитать тело
                try:
                    body = await response.text(errors='ignore')
                    print(f"\n📄 Тело ответа ({len(body)} символов):")
                    print("-" * 40)
                    
                    if body:
                        # Показываем начало и конец если длинное
                        if len(body) > 500:
                            print(body[:250])
                            print(f"\n... [пропущено {len(body) - 500} символов] ...\n")
                            print(body[-250:])
                        else:
                            print(body)
                    else:
                        print("<пустое тело>")
                        
                    print("-" * 40)
                    
                    # Проверяем на наличие null-байтов
                    if '\x00' in body:
                        print("⚠️  ВНИМАНИЕ: Обнаружены null-байты в теле ответа!")
                    
                except Exception as e:
                    print(f"\n❌ Не удалось прочитать тело: {e}")
                
                return response.status, len(body) if 'body' in locals() else 0
                
        except aiohttp.ClientConnectorError as e:
            print(f"\n❌ НЕ УДАЛОСЬ ПОДКЛЮЧИТЬСЯ: {e}")
            print("\nВозможные причины:")
            print("1. Сервер не запущен")
            print("2. Неправильный порт")
            print("3. Брандмауэр блокирует подключение")
            print("4. Сервер перегружен")
            return None, None
            
        except aiohttp.ServerTimeoutError as e:
            print(f"\n❌ ТАЙМАУТ: Сервер не отвечает ({e})")
            return None, None
            
        except Exception as e:
            print(f"\n❌ НЕОЖИДАННАЯ ОШИБКА: {type(e).__name__}: {e}")
            return None, None

async def stress_test(url, num_requests=1000, max_concurrent=50):
    """Нагрузочное тестирование с выводом ошибок"""
    print("\n" + "=" * 60)
    print(f"🔥 НАГРУЗОЧНОЕ ТЕСТИРОВАНИЕ ({num_requests:,} запросов)")
    print("=" * 60)
    
    connector = aiohttp.TCPConnector(
        limit=max_concurrent,
        limit_per_host=max_concurrent,
        ssl=False,
        force_close=True
    )
    timeout = aiohttp.ClientTimeout(total=3, connect=2, sock_read=2)
    
    # Статистика ошибок
    error_counts = {}
    success_count = 0
    failed_count = 0
    
    start_time = datetime.now()
    
    async with aiohttp.ClientSession(
        connector=connector,
        timeout=timeout
    ) as session:
        # Создаем все задачи сразу
        print(f"Создаю {num_requests} задач...")
        tasks = [make_request(session, url, i) for i in range(num_requests)]
        
        print(f"Начинаю выполнение (макс {max_concurrent} одновременных)...")
        print("-" * 60)
        
        # Обрабатываем задачи порциями для прогресса
        batch_size = 100
        for i in range(0, len(tasks), batch_size):
            batch = tasks[i:i+batch_size]
            results = await asyncio.gather(*batch)
            
            # Обрабатываем результаты батча
            for result in results:
                if result['success']:
                    success_count += 1
                else:
                    failed_count += 1
                    error_type = result['error']
                    error_counts[error_type] = error_counts.get(error_type, 0) + 1
            
            # Выводим прогресс
            processed = i + len(batch)
            elapsed = (datetime.now() - start_time).total_seconds()
            speed = processed / elapsed if elapsed > 0 else 0
            
            # Показываем последние ошибки
            last_errors = []
            if error_counts:
                for err, count in list(error_counts.items())[-3:]:
                    last_errors.append(f"{err}: {count}")
            
            print(f"Прогресс: {processed:,}/{num_requests:,} | "
                  f"✅ {success_count:,} | "
                  f"❌ {failed_count:,} | "
                  f"📊 {speed:.1f} req/sec | "
                  f"Ошибки: {', '.join(last_errors) if last_errors else 'нет'}")
            
            # Если ошибок слишком много - останавливаемся
            if failed_count > 0 and success_count == 0:
                print("\n⚠️  ВНИМАНИЕ: Все запросы завершаются ошибкой!")
                print("Прерываю тест...")
                break
    
    total_time = (datetime.now() - start_time).total_seconds()
    
    print("\n" + "=" * 60)
    print("📊 ИТОГИ ТЕСТИРОВАНИЯ")
    print("=" * 60)
    
    if success_count + failed_count > 0:
        success_rate = (success_count / (success_count + failed_count)) * 100
    else:
        success_rate = 0
    
    print(f"Общее время: {total_time:.2f} секунд")
    print(f"Всего запросов: {success_count + failed_count:,}")
    print(f"Успешных: {success_count:,}")
    print(f"С ошибками: {failed_count:,}")
    print(f"Успешность: {success_rate:.1f}%")
    print(f"Средняя скорость: {(success_count + failed_count) / total_time:.1f} запр/сек")
    
    if error_counts:
        print(f"\n📈 СТАТИСТИКА ОШИБОК:")
        for error_type, count in sorted(error_counts.items(), key=lambda x: x[1], reverse=True):
            percentage = (count / failed_count * 100) if failed_count > 0 else 0
            print(f"  {error_type}: {count:,} ({percentage:.1f}% от ошибок)")
    
    # Рекомендации
    print(f"\n💡 РЕКОМЕНДАЦИИ:")
    if failed_count == 0:
        print("  Сервер стабильно обрабатывает нагрузку")
    elif 'ConnectionError' in str(error_counts):
        print("  Проблемы с подключением - сервер может быть недоступен")
    elif 'Timeout' in str(error_counts):
        print("  Сервер не успевает обрабатывать запросы")
        print("  Увеличьте таймауты или уменьшите нагрузку")
    elif '429' in str(error_counts):  # Too Many Requests
        print("  Сервер ограничивает количество запросов")
    elif '5' in str(error_counts):  # 5xx errors
        print("  Ошибки на стороне сервера - проверьте логи сервера")

async def main():
    url = "http://localhost:6666"
    
    print(f"🎯 Целевой URL: {url}")
    print()
    
    # 1. Сначала один тестовый запрос
    status, _ = await test_single_request(url)
    
    if status is None:
        print("\n⚠️  Сервер не отвечает на одиночный запрос.")
        print("Проверьте:")
        print("  1. Запущен ли сервер?")
        print("  2. Правильный ли порт?")
        print("  3. netstat -tulpn | grep :6666")
        print()
        
        choice = input("Всё равно запустить нагрузочный тест? (y/N): ")
        if choice.lower() != 'y':
            print("Отмена.")
            return
    
    # 2. Настройка нагрузочного теста
    print("\n" + "=" * 60)
    print("⚙️  НАСТРОЙКА ТЕСТА")
    print("=" * 60)
    
    try:
        num_requests = int(input(f"Количество запросов [1000]: ") or "1000")
        max_concurrent = int(input(f"Макс одновременных запросов [50]: ") or "50")
    except ValueError:
        print("Использую значения по умолчанию")
        num_requests = 1000
        max_concurrent = 50
    
    print(f"\nБудет отправлено: {num_requests:,} запросов")
    print(f"Максимум одновременных: {max_concurrent}")
    
    confirm = input("\nНачать тест? (yes/NO): ")
    if confirm.lower() != 'yes':
        print("Отмена.")
        return
    
    # 3. Запуск нагрузочного теста
    await stress_test(url, num_requests, max_concurrent)
    
    print("\n" + "=" * 60)
    print("Тест завершен!")
    print("=" * 60)

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\n\n⏹️  Прервано пользователем")
    except Exception as e:
        print(f"\n❌ Критическая ошибка в скрипте: {e}")
        import traceback
        traceback.print_exc()