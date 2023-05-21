set(os_src "OS.cpp" "OS.h" )


add_library(OS STATIC ${os_src})
target_link_libraries(OS PRIVATE Machi::Platform)
add_library(Machi::OS ALIAS OS)