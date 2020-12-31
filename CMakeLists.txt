cmake_minimum_required(VERSION 3.17)
project(Maze)

set(CMAKE_CXX_STANDARD 17)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/1.board
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(Maze main.cpp)