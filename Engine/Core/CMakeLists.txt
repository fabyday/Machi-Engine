#

add_definitions("-DMACHI_BUILD_DLL") 
link_libraries(spdlog::spdlog)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(APPLE)
    message("Apple Platform is detected, now Metal-RHI is ON")
    add_subdirectory(MachiMetal)
elseif(WIN32)
    message("Windows Platform is detected, now DX12-RHI is ON")
    add_subdirectory(DX12-RHI)
endif()
add_subdirectory(Platform)
add_subdirectory(OS)
add_subdirectory(IO)
add_subdirectory(Application)
add_subdirectory(Graphics)



set(Machi_lib_list Machi::Application Machi::Graphics Machi::OS Machi::Platform CACHE INTERNAL "" FORCE)

