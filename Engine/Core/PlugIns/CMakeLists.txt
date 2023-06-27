
set(plugin_src  "PluginManager.cpp")
add_library(PlugIns SHARED ${plugin_src})
target_link_libraries(PlugIns PUBLIC Machi::IO Machi::Platform)
TARGET_CONFIGURE_SETUP(PlugIns "PLUGINS")

add_library(Machi::PlugIns ALIAS PlugIns)