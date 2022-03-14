add_subdirectory(Platform)
add_subdirectory(Application)

add_library(Core INTERFACE)
target_link_libraries(Core INTERFACE 
						Machi::Application 
						Machi::Platform
					)



add_library(Machi::Core ALIAS Core)