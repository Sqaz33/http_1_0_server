cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(http_1_0_server)

enable_testing()

find_package(Boost REQUIRED COMPONENTS system)

find_package(PkgConfig REQUIRED)

#http parser >
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
flex_target(
    scanner 
    src/http_lexer.l 
    ${CMAKE_BINARY_DIR}/http_lexer.cpp
)
bison_target(parser
    src/http_parser.y
    ${CMAKE_CURRENT_BINARY_DIR}/http_parser.cpp
    COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/http_parser.hpp"
)
# < http parser

file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} SHARED 
                ${SRC}                
                ${BISON_parser_OUTPUTS}
                ${FLEX_scanner_OUTPUTS})


set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED TRUE)

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

add_library(flex_bison_src STATIC ${BISON_parser_OUTPUTS} ${FLEX_scanner_OUTPUTS})
target_include_directories(flex_bison_src PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(flex_bison_src PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")

add_subdirectory("test/parse_test")
add_subdirectory("test/server_test")