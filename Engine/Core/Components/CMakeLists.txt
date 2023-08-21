set(src "Mobject.cpp" "ComponentManager.cpp"  "Renderer.cpp")
set(symbol_libs EnTT::EnTT )

set(library_deps Graphics  Logger Graphics)
ADD_MACHI_LIBRARY(Components "${src}" "${library_deps}" "${symbol_libs}")
TARGET_CONFIGURE_SETUP(Components "COMPONENTS")