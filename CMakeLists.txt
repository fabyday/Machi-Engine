cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(Machi-Engine)


# language support info

add_definitions("-DUNICODE -D_UNICODE")
if(APPLE)
#set(CMAKE_CXX_FLAGS "-std=c++17 -stdlib=libc++")
#set(CMAKE_EXE_LINKER_FLAGS "-stdlib=libc++")
endif()
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