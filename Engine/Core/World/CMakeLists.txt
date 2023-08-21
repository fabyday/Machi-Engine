set(world_src "Scene.cpp" "SceneManager.cpp")

set(symbol_libs)

set(target_libs  Logger Components)
ADD_MACHI_LIBRARY(World "${world_src}" "${target_libs}" "${symbol_libs}")
TARGET_CONFIGURE_SETUP(World "WORLD")
