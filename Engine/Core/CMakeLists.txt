#

add_definitions("-DMACHI_BUILD_DLL") 
message("init Engine-Core")


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(ENGINE_CORE_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
if(APPLE)
    message("Apple Platform is detected, now Metal-RHI is ON")
    add_subdirectory(MachiMetal)
elseif(WIN32)
    message("Windows Platform is detected, now DX12-RHI is ON")
    add_subdirectory(DX12-RHI)
endif()

link_libraries(EnTT::EnTT)

add_subdirectory(Logger)
add_subdirectory(World)
add_subdirectory(Components)
add_subdirectory(Platform)
add_subdirectory(OS)
add_subdirectory(DataStruct)
add_subdirectory(Geometry)
add_subdirectory(IO)
add_subdirectory(Application)
add_subdirectory(Graphics)
add_subdirectory(PlugIns)


set(Machi_lib_list Machi::Application Machi::Graphics Machi::Geometry Machi::IO Machi::OS Machi::Platform Machi::Logger Machi::Components Machi::World CACHE INTERNAL "" FORCE)

