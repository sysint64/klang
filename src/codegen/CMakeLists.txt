cmake_minimum_required(VERSION 2.8)

project(klang)
set(SOURCES expr.cpp)
add_library(codegen ${SOURCES})
