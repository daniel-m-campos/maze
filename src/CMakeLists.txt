configure_file(${CMAKE_CURRENT_SOURCE_DIR}/1.board
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_library(SEARCH path_finder.cpp grid.cpp)
add_executable(MAIN main.cpp)
target_link_libraries(MAIN SEARCH)