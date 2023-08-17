
set(application_src "application.cpp"  )
#add_library(Application SHARED ${application_src})
ADD_MACHI_LIBRARY(Application ${application_src} Machi::Graphics Machi::IO Machi::Geometry Machi::Platform)
#target_link_libraries(Application PUBLIC Machi::Graphics Machi::IO Machi::Geometry Machi::Platform )
TARGET_CONFIGURE_SETUP(Application "APPLICATION")
#add_library(Machi::Application ALIAS Application)