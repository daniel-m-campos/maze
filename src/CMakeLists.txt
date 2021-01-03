add_library(SEARCH path_finder.cpp grid.cpp)
add_executable(MAIN main.cpp)
target_link_libraries(MAIN SEARCH)

configure_file(${CMAKE_SOURCE_DIR}/src/1.board
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)