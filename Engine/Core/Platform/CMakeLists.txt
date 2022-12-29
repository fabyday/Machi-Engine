

if(WIN32)
set(platform_src   "windows/application.cpp"  "windows/os.cpp" "windows/machi_graphics.cpp")
elseif(APPLE)
#    set(platform_src  "Apple/entry.h" "Apple/metal-core.h" "Apple/application.cpp" "Apple/machi_graphics.cpp" "Apple/metal.cpp" )
    set(platform_src    "Apple/entry.h" "Apple/machi_graphics.cpp")
elseif(UNIX AND NOT APPLE) # linux;

endif()



#add_library(Platform SHARED ${src})

if(WIN32)
    add_library(Platform OBJECT ${platform_src})
    set(graphics_libs d3d12 dxgi dxguid d3dcompiler) #D3d12SDKLayers)
    set(platform_dependent_directory  ${platform_dependent_directory} "${CMAKE_CURRENT_SOURCE_DIR}/windows" PARENT_SCOPE) # can't use relative paths
    target_link_libraries(Platform PUBLIC ${graphics_libs})
    target_include_directories(Platform PUBLIC ${p_dir} "windows") # Windows or Apple, and Core Module Path("../..")

elseif(APPLE)
    add_library(Platform OBJECT ${platform_src})

    add_subdirectory(Apple/metal-wrapper)
    set(platform_dependent_directory  ${platform_dependent_directory} "${CMAKE_CURRENT_SOURCE_DIR}/Apple"
            PARENT_SCOPE) # can't use relative paths
    target_include_directories(Platform PUBLIC "${p_dir}" "Apple" ) # Windows or Apple, and Core Module Path("../..")

    set(platform_dependent_lib metal_wrapper PARENT_SCOPE)

elseif(UNIX AND NOT APPLE) # linux;

endif()


add_library(Machi::Platform ALIAS Platform)

