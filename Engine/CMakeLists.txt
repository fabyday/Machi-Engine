
if(WIN32)
add_definitions("-DSPDLOG_WCHAR_TO_UTF8_SUPPORT")
endif()
message("Hello and welcome Engine configuration.")
add_subdirectory(ThirdParty)
add_subdirectory(Core)
add_subdirectory(PlugIns)

if(${Editor})
add_subdirectory(Editor)

endif()	