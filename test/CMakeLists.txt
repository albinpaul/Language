cmake_minimum_required(VERSION 3.10)
set(This exampleTests)
file(GLOB Headers *.hpp)
file(GLOB Sources *.cpp)
add_executable(${This} ${Sources} ${Headers})
target_link_libraries( ${This} PUBLIC
    gtest_main
    torro
)
add_test(
    NAME ${This}
    COMMAND ${This}
)