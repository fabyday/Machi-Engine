

add_definitions("-DSPDLOG_WCHAR_TO_UTF8_SUPPORT") 

add_subdirectory(ThirdParty/spdlog)
add_subdirectory(Core)

if(${Editor})
add_subdirectory(Editor)

endif()	