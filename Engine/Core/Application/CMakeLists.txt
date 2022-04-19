set(application_src "${CMAKE_CURRENT_SOURCE_DIR}/application.cpp" )
add_library(Application OBJECT ${application_src})
#target_link_libraries(Platform INTERFACE ${graphics_libs})
#target_include_directories(Platform INTERFACE ${p_dir} "../") # Windows or Apple, and Core Module Path("../..")

add_library(Machi::Application ALIAS Application)