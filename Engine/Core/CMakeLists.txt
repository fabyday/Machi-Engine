#

add_definitions("-DMACHI_BUILD_DLL")

add_subdirectory(Platform)
add_subdirectory(OS)
add_subdirectory(Application)

add_library(Core INTERFACE)
target_link_libraries(Core INTERFACE 
						Machi::Application 
						Machi::Platform
						Machi::OS
					)

add_library(Machi::Core ALIAS Core)