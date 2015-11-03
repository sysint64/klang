cmake_minimum_required(VERSION 2.8)

project(klang)
set(SOURCES lexer.cpp)
add_library(lexer ${SOURCES})
