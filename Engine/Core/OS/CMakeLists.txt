set(header "OS.h")
set(src "OS.cpp")


add_library(OS SHARED ${src} )
target_link_libraries(OS PRIVATE Machi::Platform)


add_library(Machi::OS ALIAS OS)
