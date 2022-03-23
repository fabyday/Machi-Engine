#

add_definitions("-DMACHI_BUILD_DLL") 
link_libraries(spdlog::spdlog)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


add_subdirectory(Platform)
include_directories(${platform_dependent_directory})
add_subdirectory(OS)
add_subdirectory(Application)

add_library(Core SHARED $<TARGET_OBJECTS:Machi::Application> $<TARGET_OBJECTS:Machi::OS> $<TARGET_OBJECTS:Machi::Platform>)
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${platform_dependent_directory})
add_library(Machi::Core ALIAS Core)
