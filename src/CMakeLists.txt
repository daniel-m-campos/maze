configure_file(${CMAKE_CURRENT_SOURCE_DIR}/1.board
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(Maze main.cpp grid.cpp path_finder.cpp)