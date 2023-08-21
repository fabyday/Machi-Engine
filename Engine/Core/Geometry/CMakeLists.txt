set(src "Mesh.cpp" )

set(target_lib Logger)
set(symbol_libs )
ADD_MACHI_LIBRARY(Geometry "${src}" "${target_libs}" "${symbol_libs}")
TARGET_CONFIGURE_SETUP(Geometry "GEOMETRY")
