cmake_minimum_required(VERSION 2.8)

project(klang)
set(SOURCES parser.cpp expr.cpp function.cpp type.cpp)
add_library(parser ${SOURCES})
target_link_libraries(parser lexer)
