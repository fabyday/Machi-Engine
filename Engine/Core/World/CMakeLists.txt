set(world_src "Scene.cpp")


add_library(World SHARED ${world_src})
TARGET_CONFIGURE_SETUP(World "WORLD")

# target_link_libraries(Graphics PUBLIC metal_wrapper)
target_link_libraries(World PRIVATE Machi::Logger Machi::Components)
add_library(Machi::World ALIAS World)