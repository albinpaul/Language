cmake_minimum_required(VERSION 3.10)
set( gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)
project(TorroProject VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(--std=c++17)
enable_testing()
include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
    )

add_subdirectory(src)
add_subdirectory(test)