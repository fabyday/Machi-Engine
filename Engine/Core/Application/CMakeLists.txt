
set(application_src "application.cpp"  )
add_library(Application SHARED ${application_src})
target_link_libraries(Application PRIVATE Machi::Graphics Machi::IO Machi::Geometry)
TARGET_CONFIGURE_SETUP(Application "APPLICATION")

add_library(Machi::Application ALIAS Application)