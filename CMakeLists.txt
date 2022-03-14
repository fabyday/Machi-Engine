cmake_minimum_required(VERSION 3.10)

project(Machi-Engine)



option(Editor OFF "editor")
option(Testbed ON "testbed")




add_subdirectory("Engine")
add_subdirectory("Test")

if(${Testbed})
message("test is ON")
add_subdirectory("Test")
endif()