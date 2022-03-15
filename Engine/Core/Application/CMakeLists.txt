set(header "application.h")
set(src "application.cpp")


add_library(Application SHARED ${src} )
target_link_libraries(Application PUBLIC Machi::Platform)
add_library(Machi::Application ALIAS Application)
