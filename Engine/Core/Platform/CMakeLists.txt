
set(p_dir)
set(src)
set(graphics_libs)


if(WIN32)
set(p_dir windows)
#set(src "windows/machi_graphics.cpp"  "windows/application.cpp"  "windows/os.cpp" "windows/math_component.h")
set(src   "windows/application.cpp"  "windows/os.cpp" )
set(graphics_libs d3d12 dxgi dxguid d3dcompiler) #D3d12SDKLayers)
elseif(APPLE)
    set(p_dir Apple)
    set(src   "Apple/appspec.cpp" "Apple/machi_graphics.cpp")
elseif(UNIX AND NOT APPLE) # linux;

endif()

#add_library(Platform SHARED ${src})
add_library(Platform STATIC ${src})
target_link_libraries(Platform ${graphics_libs})
target_include_directories(Platform PUBLIC ${p_dir} "../") # Windows or Apple, and Core Module Path("../..")

add_library(Machi::Platform ALIAS Platform)

