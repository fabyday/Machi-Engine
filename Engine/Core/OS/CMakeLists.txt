set(os_src "OS.cpp" )


add_library(OS OBJECT ${os_src})
#target_link_libraries(Platform INTERFACE ${graphics_libs})
#target_include_directories(Platform INTERFACE ${p_dir} "../") # Windows or Apple, and Core Module Path("../..")

add_library(Machi::OS ALIAS OS)