cmake_minimum_required(VERSION 3.5)
project(MAZE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
string(APPEND CMAKE_CXX_FLAGS " -Wall")

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)

enable_testing()
