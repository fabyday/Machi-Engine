#target_link_libraries(Platform INTERFACE ${graphics_libs})
#target_include_directories(Platform INTERFACE ${p_dir} "../") # Windows or Apple, and Core Module Path("../..")
set(graphcis_header "native_format_converter.h")
set(graphics_src "RootSignature.cpp" "RootSignature.h" "NativeGraphicsManager.cpp" 
"Device.cpp" "CommandQueue.cpp" "SwapChain.cpp" "CommandAllocator.cpp" 
"Synchronizer.h" "PipelineStateObject.cpp" "Shader.h" "Shader.cpp")
add_library(DX12-RHI STATIC ${graphics_src} ${graphcis_header})
add_library(Machi::DX12-RHI ALIAS DX12-RHI)