
set(platform_src )
set(target_libs)
set(symbol_libs)

if(WIN32)
    set(platform_src   "windows/windows_platform.cpp"  "windows/console.cpp" "inputs.cpp" )

elseif(APPLE)
#    set(platform_src  "Apple/entry.h" "Apple/metal-core.h" "Apple/application.cpp" "Apple/machi_graphics.cpp" "Apple/metal.cpp" )
    set(platform_src  "Apple/apple_delegate.h"   "Apple/apple_delegate.cpp"
            ../Graphics/machi_graphics.cpp)

elseif(UNIX AND NOT APPLE) # linux;
endif()

if(WIN32)
    # set(MODULE_NAME "PLATFORM")
    # configure_file(windows/config.h.in config.h @ONLY)
    # target_include_directories(Platform PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
    set( symbol_libs "winmm.lib")
elseif(APPLE)
    #target_include_directories(Platform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} Apple)
elseif(UNIX AND NOT APPLE) # linux;
endif()

list(APPEND target_libs Logger Graphics IO Geometry)
ADD_MACHI_LIBRARY(Platform "${platform_src}" "${target_libs}" "${symbol_libs}")
TARGET_CONFIGURE_SETUP(Platform "PLATFORM")
target_include_directories(Platform_object PUBLIC  "windows") # Windows or Apple, and Core Module Path("../..")



