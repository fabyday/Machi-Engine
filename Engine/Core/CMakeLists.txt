#

add_definitions("-DMACHI_BUILD_DLL") 
message("init Engine-Core")


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(ENGINE_CORE_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")


link_libraries(EnTT::EnTT spdlog::spdlog )

if(APPLE)
    message("Apple Platform is detected, now Metal-RHI is ON")
    add_subdirectory(MachiMetal)
elseif(WIN32)
    message("Windows Platform is detected, now DX12-RHI is ON")
    add_subdirectory(DX12-RHI)
endif()


add_subdirectory(Platform)
add_subdirectory(Logger)
add_subdirectory(World)
add_subdirectory(Components)
add_subdirectory(OS)
add_subdirectory(DataStruct)
add_subdirectory(Geometry)
add_subdirectory(IO)
add_subdirectory(Application)
add_subdirectory(Graphics)
#add_subdirectory(PlugIns)

set(tgt_name DX12_RHI Application Platform Logger World Components OS DataStruct Geometry IO Application Graphics)
#add_library(Machi::DX12_RHI ALIAS DX12_RHI)
ADD_NAMESPACE("${tgt_name}")
set(Machi_lib_list Machi::Application Machi::DX12_RHI Machi::Graphics Machi::Geometry Machi::IO Machi::OS Machi::Platform Machi::Logger Machi::Components Machi::World CACHE INTERNAL "" FORCE)
#set(Machi_lib_list Machi::Application  CACHE INTERNAL "" FORCE)

