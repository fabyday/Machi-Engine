add_definitions("-DDX12_INNER_ONLY_INCLUDE")
set(graphcis_header "Commons.h" "native_format_converter.h")
set(graphics_src "RootSignature.cpp" "RootSignature.h" "NativeGraphicsManager.cpp" 
"Device.cpp" "CommandQueue.cpp" "SwapChain.cpp" "CommandAllocator.cpp" 
"Synchronizer.cpp" "PipelineStateObject.cpp" "Shader.h" "Shader.cpp" "DescriptorHeap.cpp" "add_dx12.cpp")
add_library(DX12-RHI STATIC ${graphics_src} ${graphcis_header})
target_link_libraries(DX12-RHI PUBLIC Machi::Platform)
add_library(Machi::DX12-RHI ALIAS DX12-RHI)
