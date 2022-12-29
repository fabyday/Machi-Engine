cmake_minimum_required(VERSION 3.10)

project(Machi-Engine)


# language support info
set(CMAKE_CXX_STANDARD 17)

add_definitions("-DUNICODE -D_UNICODE")


# set cmakes files

#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
#SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
#SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
#SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
#SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
#SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
include(cmakes/dependency_helper.cmake)

option(Editor OFF "editor")
option(Testbed ON "testbed")
message("${Testbed}")
add_subdirectory("Engine")

    message("test")
if(${Testbed})
add_subdirectory("Test")
endif()