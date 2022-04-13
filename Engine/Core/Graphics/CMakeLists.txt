set(graphics_src "${CMAKE_CURRENT_SOURCE_DIR}/GraphicManager.cpp" )
message("asdasds  ${application_src}")
add_library(Graphics OBJECT ${graphics_src})
#target_link_libraries(Platform INTERFACE ${graphics_libs})
#target_include_directories(Platform INTERFACE ${p_dir} "../") # Windows or Apple, and Core Module Path("../..")

add_library(Machi::Graphics ALIAS Graphics)