set(world_src "Scene.cpp")


add_library(World SHARED ${world_src})
#target_link_libraries(OS PRIVATE Machi::Platform)
add_library(Machi::World ALIAS World)