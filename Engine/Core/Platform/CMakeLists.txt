if(WIN32)
set(p_dir windows)
elseif(APPLE)

elseif(UNIX AND NOT APPLE) # linux;

endif()


add_library(Platform INTERFACE)
target_include_directories(Platform INTERFACE ${p_dir})
add_library(Machi::Platform ALIAS Platform)
