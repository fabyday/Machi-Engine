
set(application_src "application.cpp"  )
#add_library(Application SHARED ${application_src})
set(library_deps Graphics IO Geometry Platform)
set(symbol_libs)
add_definitions(-D)
ADD_MACHI_LIBRARY(Application "${application_src}" "${library_deps}" "${symbol_libs}")
TARGET_CONFIGURE_SETUP(Application "APPLICATION")
