cmake_minimum_required(VERSION 2.8)

project(klang)
set(SOURCES type.cpp)
add_library(ast ${SOURCES})
