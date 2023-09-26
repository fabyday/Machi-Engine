add_definitions("-DDX12_INNER_ONLY_INCLUDE")
set(graphcis_header "Commons.h" "native_format_converter.h" "Matrix.h")
set(graphics_src "RootSignature.cpp" "RootSignature.h" "NativeGraphicsManager.cpp" 
"Device.cpp" "CommandQueue.cpp" "SwapChain.cpp" "CommandAllocator.cpp" 
"Synchronizer.cpp" "PipelineStateObject.cpp" "Shader.h" "Shader.cpp" "DescriptorHeap.cpp" "add_dx12.cpp"  "Matrix.cpp")
set(symbol_libs)
set(target_libs )

list(APPEND symbol_libs )
list(APPEND target_libs Platform Graphics Logger )
#add_library(DX12_RHI STATIC ${graphics_src})
#target_link_libraries(DX12_RHI PUBLIC Platform_static)


ADD_MACHI_LIBRARY(DX12_RHI "${graphics_src}" "${target_libs}" "${symbol_libs}")
TARGET_CONFIGURE_SETUP(DX12_RHI "DX12_RHI")
