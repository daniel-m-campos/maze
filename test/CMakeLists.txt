include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(TEST test.cpp)
target_include_directories(TEST PUBLIC "${CMAKE_SOURCE_DIR}/src")
target_link_libraries(TEST Catch2::Catch2WithMain SEARCH)

configure_file(
        ${CMAKE_SOURCE_DIR}/src/5x6.board
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(TEST)
