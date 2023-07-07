set(src "Mesh.cpp" )

add_library(Geometry SHARED ${src} )
TARGET_CONFIGURE_SETUP(Geometry "GEOMETRY")
target_link_libraries(Geometry PUBLIC Machi::Logger)
add_library(Machi::Geometry ALIAS Geometry)
