include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/54915d462bb64e9b2bd1a3f0e70c00e6f5d817fb.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(http_request_parser_test test.cpp ${SRC})

target_include_directories(http_request_parser_test PRIVATE "${CMAKE_SOURCE_DIR}/src")
target_include_directories(http_request_parser_test  PRIVATE "${CMAKE_BINARY_DIR}")

target_link_libraries(http_request_parser_test PRIVATE flex_bison_src)
    
set_property(TARGET http_request_parser_test PROPERTY CXX_STANDARD 20)
set_property(TARGET http_request_parser_test PROPERTY CXX_STANDARD_REQUIRED TRUE)

target_link_libraries(http_request_parser_test PRIVATE GTest::gtest)

add_test(NAME http_request_parser_test COMMAND http_request_parser_test)



