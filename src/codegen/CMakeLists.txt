cmake_minimum_required(VERSION 2.8)

project(klang)
set(SOURCES expr.cpp function.cpp type.cpp)
add_library(codegen ${SOURCES})
