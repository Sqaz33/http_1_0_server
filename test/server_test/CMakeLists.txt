include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/54915d462bb64e9b2bd1a3f0e70c00e6f5d817fb.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(server_test test.cpp)

target_link_libraries(server_test PRIVATE ${PROJECT_NAME})
