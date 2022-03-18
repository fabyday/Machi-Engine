
set(p_dir)
set(src)
set(graphics_libs)

if(WIN32)
set(p_dir windows)
set(src "windows/machi_graphics.cpp" "windows/types.h" "windows/appspec.cpp" "windows/os.h" "windows/os.cpp" "windows/math_component.h")
set(graphics_libs d3d12 dxgi dxguid d3dcompiler) #D3d12SDKLayers)
elseif(APPLE)

elseif(UNIX AND NOT APPLE) # linux;

endif()

message(${src})
add_library(Platform SHARED ${src})
target_link_libraries(Platform ${graphics_libs})
target_include_directories(Platform PUBLIC ${p_dir})

add_library(Machi::Platform ALIAS Platform)