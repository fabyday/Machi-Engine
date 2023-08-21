set(src "Logger.cpp" "Logger.h")



set(symbol_libs spdlog::spdlog)
set(target_libs )
ADD_MACHI_LIBRARY(Logger "${src}" "${target_libs}" "${symbol_libs}")
TARGET_CONFIGURE_SETUP(Logger "LOGGER")
