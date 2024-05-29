add_library(SEARCH path_finder.cpp grid.cpp)
add_executable(MAZE main.cpp)
target_link_libraries(MAZE SEARCH)

configure_file(
        ${CMAKE_SOURCE_DIR}/src/5x6.board
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY
)
