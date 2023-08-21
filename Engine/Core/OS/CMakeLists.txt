set(os_src "OS.cpp")




set(symbol_libs)
set(target_libs Platform)
ADD_MACHI_LIBRARY(OS "${os_src}" "${target_libs}" "${symbol_libs}")
TARGET_CONFIGURE_SETUP(OS "OS")
