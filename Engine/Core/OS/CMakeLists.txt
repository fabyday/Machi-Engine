set(os_src "OS.cpp" OS.h )


add_library(OS STATIC ${os_src})

add_library(Machi::OS ALIAS OS)