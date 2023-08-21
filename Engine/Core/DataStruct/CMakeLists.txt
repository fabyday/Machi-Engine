set(src "Matrix.cpp")

set(library_deps)
set(symbol_libs)
ADD_MACHI_LIBRARY(DataStruct "${src}" "${library_deps}" "${symbol_libs}")
TARGET_CONFIGURE_SETUP(DataStruct "DATASTRUCTURE")