

if(WIN32)
set(platform_src   "windows/application.cpp"  "windows/os.cpp")
set(platform_lib d3d12 dxgi dxguid d3dcompiler) #D3d12SDKLayers)
set(platform_dependent_directory  ${platform_dependent_directory} "${CMAKE_CURRENT_SOURCE_DIR}/windows" PARENT_SCOPE) # can't use relative paths
elseif(APPLE)
    set(platform_src   "Apple/appspec.cpp" "Apple/machi_graphics.cpp" )
set(platform_dependent_directory  ${platform_dependent_directory} "${CMAKE_CURRENT_SOURCE_DIR}/Apple" PARENT_SCOPE) # can't use relative paths
elseif(UNIX AND NOT APPLE) # linux;

endif()



#add_library(Platform SHARED ${src})
add_library(Platform OBJECT ${platform_src})
target_link_libraries(Platform PUBLIC ${graphics_libs})
target_include_directories(Platform PUBLIC ${p_dir} "windows") # Windows or Apple, and Core Module Path("../..")
add_library(Machi::Platform ALIAS Platform)

