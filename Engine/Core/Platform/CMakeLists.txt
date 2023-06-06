

if(WIN32)
    set(platform_src   "windows/windows_platform.cpp"  "windows/console.cpp" )

elseif(APPLE)
#    set(platform_src  "Apple/entry.h" "Apple/metal-core.h" "Apple/application.cpp" "Apple/machi_graphics.cpp" "Apple/metal.cpp" )
    set(platform_src  "Apple/apple_delegate.h"   "Apple/apple_delegate.cpp"
            ../Graphics/machi_graphics.cpp)

elseif(UNIX AND NOT APPLE) # linux;

endif()

#add_library(Platform SHARED ${src})
add_library(Platform SHARED ${platform_src})

if(WIN32)
    set(platform_dependent_directory  ${platform_dependent_directory} "${CMAKE_CURRENT_SOURCE_DIR}/windows" PARENT_SCOPE) # can't use relative paths
    target_include_directories(Platform PUBLIC ${p_dir} "windows") # Windows or Apple, and Core Module Path("../..")
    # set(MODULE_NAME "PLATFORM")
    # configure_file(windows/config.h.in config.h @ONLY)
    # target_include_directories(Platform PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
   
    TARGET_CONFIGURE_SETUP(Platform "PLATFORM")
    message("mod ${MODULE_NAME}")


elseif(APPLE)
    target_include_directories(Platform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} Apple)
elseif(UNIX AND NOT APPLE) # linux;
    
endif()

add_library(Machi::Platform ALIAS Platform)

