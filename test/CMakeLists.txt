add_executable(TEST test.cpp)
target_include_directories(TEST PUBLIC "${CMAKE_SOURCE_DIR}/src")
target_link_libraries(TEST Catch2 SEARCH)

configure_file(${CMAKE_SOURCE_DIR}/src/1.board
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)