#include "con_manager.hpp"

#include <atomic>
#include <algorithm>
#include <mutex>
#include <utility>

namespace http_server {

namespace detail__ {

std::mutex mut;
bool end = false;

void ConnectionManager::start(connection::IConSharedPtr con) {
    {
        std::lock_guard lc(mut); 
        if (!end) {
            cons_[con.get()] = con;
        }
    }
    con->start();

}

void ConnectionManager::stop(connection::IConSharedPtr con) {
    {
        std::lock_guard lc(mut);
        if (!end) {
            cons_.erase(con.get());
        }
    }
    con->stop();

}

void ConnectionManager::stopAll() {
    std::lock_guard lc(mut);
    end = true;
    std::for_each(cons_.begin(), cons_.end(), 
        [] (auto&& con) { con.second->stop(); });
    cons_.clear();
}   

} // namespace detail__

} // namespace http_server