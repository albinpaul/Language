cmake_minimum_required(VERSION 3.10)
set( gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)
project(Torro VERSION 1.0)
enable_testing()
include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
    )

add_subdirectory(src)
add_subdirectory(test)