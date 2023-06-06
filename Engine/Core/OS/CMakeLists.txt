set(os_src "OS.cpp")


add_library(OS SHARED ${os_src})
target_link_libraries(OS PRIVATE Machi::Platform)
    TARGET_CONFIGURE_SETUP(OS "OS")
    message("${MODULE_NAME}")
add_library(Machi::OS ALIAS OS)