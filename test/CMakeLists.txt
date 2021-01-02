project(tests)
add_executable(tests test.cpp)
target_link_libraries(tests Catch2)