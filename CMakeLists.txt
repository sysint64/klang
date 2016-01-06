cmake_minimum_required(VERSION 2.8)

project(klang)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
#set(Boost_NO_SYSTEM_PATHS ON)
#set(SFML_NO_SYSTEM_PATHS ON)

if (APPLE)
	set(PLATFORM _osx_)
elseif(UNIX)
	set(PLATFORM _linux_)
else()
	set(PLATFORM _win_)
endif()

add_definitions(-D${PLATFORM})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(DEBUG_FLAGS "${CMAKE_CXX_FLAGS} -g3 -O0 -Wno-deprecated-declarations")
set(RELEASE_FLAGS_32 "${CMAKE_CXX_FLAGS} -m32 -mfpmath=sse -Ofast -flto -march=native -funroll-loops -Wno-deprecated-declarations")
set(RELEASE_FLAGS_64 "${CMAKE_CXX_FLAGS} -m64 -mfpmath=sse -Ofast -flto -march=native -funroll-loops -Wno-deprecated-declarations")

if (APPLE)
	set(CMAKE_CXX_FLAGS "${DEBUG_FLAGS} -std=c++14 -stdlib=libc++")
	include_directories(~/Documents/libcxx/include)
else()
	set(CMAKE_CXX_FLAGS "${DEBUG_FLAGS} -std=c++14")
endif()

set(SOURCE_EXE src/main.cpp src/compiler.cpp src/cmd.cpp)

add_executable(main ${SOURCE_EXE})

find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(include src/lexer src/parser src/codegen)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(src/ast)
add_subdirectory(src/lexer)
add_subdirectory(src/parser)
add_subdirectory(src/codegen)

target_link_libraries(main ast lexer parser codegen)
