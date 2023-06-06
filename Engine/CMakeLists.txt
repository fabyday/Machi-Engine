
if(WIN32)
add_definitions("-DSPDLOG_WCHAR_TO_UTF8_SUPPORT")
endif()

add_subdirectory(ThirdParty/spdlog)
add_subdirectory(Core)

if(${Editor})
add_subdirectory(Editor)

endif()	