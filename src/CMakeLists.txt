cmake_minimum_required(VERSION 3.10)
set(This Torro)
file(GLOB Headers *.hpp)
file(GLOB Sources *.cpp)


add_executable(${This} "")
target_sources(${This}
    PRIVATE ${Sources} 
    PUBLIC ${Headers}
)
add_subdirectory(torro)
target_link_libraries(${This} torro)

# install(TARGETS ${This} DESTINATION bin)