#

add_definitions("-DMACHI_BUILD_DLL") 
link_libraries(spdlog::spdlog)

if(APPLE)
    message("metal is ON")
    add_subdirectory(MachiMetal)
endif()
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(OS)
add_subdirectory(Application)
add_subdirectory(Graphics)
add_subdirectory(DX12-RHI)
add_subdirectory(Platform)



set(Machi_lib_list Machi::Application Machi::Graphics Machi::OS Machi::Platform CACHE INTERNAL "" FORCE)

