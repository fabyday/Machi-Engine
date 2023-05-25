
set(application_src "application.cpp"  )
add_library(Application SHARED ${application_src})
target_link_libraries(Application PRIVATE Machi::Graphics)
add_library(Machi::Application ALIAS Application)