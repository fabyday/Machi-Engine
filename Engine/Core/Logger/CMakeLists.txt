set(src "Logger.cpp" "Logger.h")

add_library(Logger SHARED ${src} )
TARGET_CONFIGURE_SETUP(Logger "LOGGER")
target_link_libraries(Logger PUBLIC spdlog::spdlog)
add_library(Machi::Logger ALIAS Logger)
