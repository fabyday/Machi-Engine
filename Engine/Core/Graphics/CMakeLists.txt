#target_link_libraries(Platform INTERFACE ${graphics_libs})
#target_include_directories(Platform INTERFACE ${p_dir} "../") # Windows or Apple, and Core Module Path("../..")



set(graphics_src  "GraphicManager.cpp"  "machi_graphics.cpp" )
set(target_libs)
set(symbol_libs)

if(WIN32)
message("DX12-backend is appended to Graphics library")
list(APPEND target_libs Platform)
list(APPEND symbol_libs DX12_RHI)
    message("${MODULE_NAME}")
elseif(APPLE)
list(APPEND target_libs metal_wrapper Platform)
message("metal-backend is appended to Graphics library")
endif()




ADD_MACHI_LIBRARY(Graphics "${graphics_src}" "${target_libs}" "${symbol_libs}")
TARGET_CONFIGURE_SETUP(Graphics "GRAPHICS")
