add_executable(TEST test.cpp)
target_include_directories(TEST PUBLIC "${CMAKE_SOURCE_DIR}/src")
target_link_libraries(TEST Catch2 SEARCH)

