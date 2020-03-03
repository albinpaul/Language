cmake_minimum_required(VERSION 3.10)
set(This torro)
file(GLOB Headers *.hpp)
file(GLOB Sources *.cpp)


add_library(${This} "")
target_sources(${This}
    PRIVATE ${Sources} 
    PUBLIC ${Headers}
)

target_include_directories(
    ${This}
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}
)