set(header "application.h")
set(src "application.cpp")


add_library(Application SHARED ${src} )
target_compile_definitions(Application PRIVATE MACHI_BUILD_DLL)
target_link_libraries(Application PUBLIC Machi::Platform)
add_library(Machi::Application ALIAS Application)
