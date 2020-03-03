cmake_minimum_required(VERSION 3.10)
set(This torro)
file(GLOB Headers *.hpp)
file(GLOB Sources *.cpp)


add_library(${This} STATIC ${Sources} ${Headers})
target_include_directories(
    ${This}
    PUBLIC include
)