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

set(DEFINE_TRACE "")
configure_file(src/http_parser.y.in src/http_parser.y @ONLY)
bison_target(parser
    "${CMAKE_CURRENT_BINARY_DIR}/src/http_parser.y"
    "${CMAKE_CURRENT_BINARY_DIR}/http_parser.cpp"
    COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/http_parser.hpp"
)

set(DEFINE_TRACE "%define parse.trace")
configure_file(src/http_parser.y.in src/debug_http_parser.y @ONLY)
bison_target(debug_parser
    "${CMAKE_CURRENT_BINARY_DIR}/src/debug_http_parser.y"
    "${CMAKE_CURRENT_BINARY_DIR}/debug_http_parser.cpp"
    COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/debug_http_parser.hpp"
)

add_library(flex_bison_src STATIC ${BISON_debug_parser_OUTPUTS} ${FLEX_scanner_OUTPUTS})
target_include_directories(flex_bison_src PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(flex_bison_src PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
target_compile_definitions(flex_bison_src PUBLIC DEBUG_PARSER)

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



add_subdirectory("test/parse_test")
add_subdirectory("test/server_test")