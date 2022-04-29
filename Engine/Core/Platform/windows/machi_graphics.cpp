//MIT License 
//Copyright(c) 2022 Ji Hyun Roh
// 
// 
//Permission is hereby granted, free of charge, to any person
//obtaining a copy of this softwareand associated documentation
//files(the "Software"), to deal in the Software without
//restriction, including without limitation the rights to use,
//copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the
//Software is furnished to do so, subject to the following
//conditions :
//
//The above copyright noticeand this permission notice shall be
//included in all copies or substantial portions of the Software.
// 
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//OTHER DEALINGS IN THE SOFTWARE.

#include <Graphics/GraphicManager.h>
#include "config.h"
#include "d3d12.h"
#include "d3dx12.h"
#include "os_native.h"
#include "dxhelper.h"
#include <wrl.h> // ComPtr header
#include <shellapi.h>

#include <directxmath.h>
#include <D3Dcompiler.h>
#include <dxgi1_4.h>


#include <d3d12sdklayers.h> // for debugging

#include <DirectXMath.h>
#include <spdlog/spdlog.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")



template <typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;
using namespace DirectX;

struct Vertex
{
    XMFLOAT3 position;
    XMFLOAT4 color;
};
typedef struct Buffer {
    template <typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;


    ComPtr<ID3D12Resource> buffer_;
    Buffer() {};

} Buffer;

typedef struct BufferView {
    D3D12_VERTEX_BUFFER_VIEW buffer_view_;
    MUINT size_in_byte_;
    MUINT stride_in_bytes_;

    BufferView(Buffer* buf,
        UINT                      SizeInBytes,
        UINT                      StrideInBytes) {

    }
}BufferView;

typedef struct SyncronizeDesc {
    UINT frame_index_;
    HANDLE fence_event_;
    ComPtr<ID3D12Fence> fence_;
    UINT64 fenceValue_;
}SyncronizeObejct;

typedef struct GraphicsDesc {
    D3D12_VIEWPORT viewport_;
    D3D12_RECT scissor_rect_;
    ComPtr<IDXGISwapChain3> swap_chain_;
    ComPtr<ID3D12Device> device_;
    ComPtr<ID3D12Resource> render_targets_[2];
    ComPtr<ID3D12CommandAllocator> command_allocator_;
    ComPtr<ID3D12CommandQueue> command_queue_;
    ComPtr<ID3D12RootSignature> root_signature_;
    
    ComPtr<ID3D12DescriptorHeap> rtv_heap_;
    ComPtr<ID3D12DescriptorHeap> srv_heap_;


    ComPtr<ID3D12PipelineState> pipeline_state_;
    ComPtr<ID3D12GraphicsCommandList> command_list_;
    UINT rtv_descriptor_size_;

    ComPtr<ID3D12Resource> vertex_buffer_;
    D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view_;
    ComPtr<ID3D12Resource> texture_;
}GraphicsContext;

void WaitForPreviousFrame(GraphicsContext& g, SyncronizeObejct& s);
// Generate a simple black and white checkerboard texture.
std::vector<UINT8> gen_texture(UINT TextureWidth, UINT TextureHeight, UINT TexturePixelSize)
{
    const UINT rowPitch = TextureWidth * TexturePixelSize;
    const UINT cellPitch = rowPitch >> 3;        // The width of a cell in the checkboard texture.
    const UINT cellHeight = TextureWidth >> 3;    // The height of a cell in the checkerboard texture.
    const UINT textureSize = rowPitch * TextureHeight;

    std::vector<UINT8> data(textureSize);
    UINT8* pData = &data[0];

    for (UINT n = 0; n < textureSize; n += TexturePixelSize)
    {
        UINT x = n % rowPitch;
        UINT y = n / rowPitch;
        UINT i = x / cellPitch;
        UINT j = y / cellHeight;

        if (i % 2 == j % 2)
        {
            pData[n] = 0x00;        // R
            pData[n + 1] = 0x00;    // G
            pData[n + 2] = 0x00;    // B
            pData[n + 3] = 0xff;    // A
        }
        else
        {
            pData[n] = 0xff;        // R
            pData[n + 1] = 0xff;    // G
            pData[n + 2] = 0xff;    // B
            pData[n + 3] = 0xff;    // A
        }
    }

    return data;
}
static void load_assets(GraphicsContext& g, SyncronizeObejct& s) {
    

    //create rootsignature
    {
        D3D12_FEATURE_DATA_ROOT_SIGNATURE feature_data = {};
        feature_data.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;

        if (FAILED(g.device_->CheckFeatureSupport(D3D12_FEATURE_ROOT_SIGNATURE, &feature_data, sizeof(feature_data)))) {
            feature_data.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_0;
        }
        CD3DX12_DESCRIPTOR_RANGE1 ranges[1];
        ranges[0].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);

        CD3DX12_ROOT_PARAMETER1 rootParameters[1];
        rootParameters[0].InitAsDescriptorTable(1, &ranges[0], D3D12_SHADER_VISIBILITY_PIXEL);

        D3D12_STATIC_SAMPLER_DESC sampler = {};
        sampler.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
        sampler.AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
        sampler.AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
        sampler.AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
        sampler.MipLODBias = 0;
        sampler.MaxAnisotropy = 0;
        sampler.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
        sampler.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
        sampler.MinLOD = 0.0f;
        sampler.MaxLOD = D3D12_FLOAT32_MAX;
        sampler.ShaderRegister = 0;
        sampler.RegisterSpace = 0;
        sampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

        //CD3DX12_ROOT_SIGNATURE_DESC rootsignatureDesc;
        //rootsignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
        CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
        rootSignatureDesc.Init_1_1(_countof(rootParameters), rootParameters, 1, &sampler, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

        ComPtr<ID3DBlob> signature;
        ComPtr<ID3DBlob> error;
        //ThrowIfFailed(D3D12SerializeRootSignature(&rootsignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
        ThrowIfFailed(D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, feature_data.HighestVersion, &signature, &error));
        ThrowIfFailed(g.device_->CreateRootSignature(0, 
                                signature->GetBufferPointer(), 
                                signature->GetBufferSize(), 
                                IID_PPV_ARGS(&g.root_signature_))
                    );
    }
    //create pipeline state
    {
        ComPtr<ID3DBlob> vertex_shader;
        ComPtr<ID3DBlob> pixel_shader;
#if defined(_DEBUG)
        // Enable better shader debugging with the graphics debugging tools.
        UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
        UINT compileFlags = 0;
#endif
        ThrowIfFailed(D3DCompileFromFile(L"resources/shader/test_vertex_shader.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &vertex_shader, nullptr));
        ThrowIfFailed(D3DCompileFromFile(L"resources/shader/test_pixel_shader.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &pixel_shader, nullptr));
        // Define the vertex input layout.
        D3D12_INPUT_ELEMENT_DESC input_element_descs[] =
        {
           { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
           { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
        };

        // Describe and create the graphics pipeline state object (PSO).
        D3D12_GRAPHICS_PIPELINE_STATE_DESC pso_desc = {};
        pso_desc.InputLayout = { input_element_descs, _countof(input_element_descs) };
        pso_desc.pRootSignature = g.root_signature_.Get();
        pso_desc.VS = CD3DX12_SHADER_BYTECODE(vertex_shader.Get());
        pso_desc.PS = CD3DX12_SHADER_BYTECODE(pixel_shader.Get());
        pso_desc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
        pso_desc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
        pso_desc.DepthStencilState.DepthEnable = FALSE;
        pso_desc.DepthStencilState.StencilEnable = FALSE;
        pso_desc.SampleMask = UINT_MAX;
        pso_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        pso_desc.NumRenderTargets = 1;
        pso_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        pso_desc.SampleDesc.Count = 1;

        ThrowIfFailed(g.device_->CreateGraphicsPipelineState(&pso_desc, IID_PPV_ARGS(&g.pipeline_state_)));
    }


//create command list
    ThrowIfFailed(g.device_->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, g.command_allocator_.Get(), g.pipeline_state_.Get(), IID_PPV_ARGS(&g.command_list_)));
    // recording state(must be closed)
    ThrowIfFailed(g.command_list_->Close());
    

    float m_aspectRatio = static_cast<float>(1280) / static_cast<float>(960);


    // Create the vertex buffer.
    {
        // Define the geometry for a triangle.
        Vertex triangleVertices[] =
        {
            { { 0.0f, 0.25f * m_aspectRatio, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
            { { 0.25f, -0.25f * m_aspectRatio, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
            { { -0.25f, -0.25f * m_aspectRatio, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
        };

        const UINT vertexBufferSize = sizeof(triangleVertices);

        // Note: using upload heaps to transfer static data like vert buffers is not 
        // recommended. Every time the GPU needs it, the upload heap will be marshalled 
        // over. Please read up on Default Heap usage. An upload heap is used here for 
        // code simplicity and because there are very few verts to actually transfer.
        ThrowIfFailed(g.device_->CreateCommittedResource(
            &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
            D3D12_HEAP_FLAG_NONE,
            &CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize),
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&g.vertex_buffer_)));

        // Copy the triangle data to the vertex buffer.
        UINT8* pVertexDataBegin;
        CD3DX12_RANGE readRange(0, 0);        // We do not intend to read from this resource on the CPU.
        ThrowIfFailed(g.vertex_buffer_->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin)));
        memcpy(pVertexDataBegin, triangleVertices, sizeof(triangleVertices));
        g.vertex_buffer_->Unmap(0, nullptr);

        // Initialize the vertex buffer view.
        g.vertex_buffer_view_.BufferLocation = g.vertex_buffer_->GetGPUVirtualAddress();
        g.vertex_buffer_view_.StrideInBytes = sizeof(Vertex);
        g.vertex_buffer_view_.SizeInBytes = vertexBufferSize;
    }


    //load texture
    ComPtr<ID3D12Resource> texture_upload_heap;
    {
        D3D12_RESOURCE_DESC texture_desc= {};
        texture_desc.MipLevels = 1;
        texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        texture_desc.Width = 256;
        texture_desc.Height = 256;
        texture_desc.Flags = D3D12_RESOURCE_FLAG_NONE;
        texture_desc.DepthOrArraySize = 1;
        texture_desc.SampleDesc.Count = 1;
        texture_desc.SampleDesc.Quality = 0;
        texture_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;


        ThrowIfFailed(g.device_->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
                                D3D12_HEAP_FLAG_NONE,
                                &texture_desc,
                                D3D12_RESOURCE_STATE_COPY_DEST, 
                                nullptr, 
                                IID_PPV_ARGS(&g.texture_)));
        const MINT64 upload_buffer_size = GetRequiredIntermediateSize(g.texture_.Get(), 0, 1);



        ThrowIfFailed(g.device_->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
                                D3D12_HEAP_FLAG_NONE,
                                &CD3DX12_RESOURCE_DESC::Buffer(upload_buffer_size), 
                                D3D12_RESOURCE_STATE_GENERIC_READ, 
                                nullptr, 
                                IID_PPV_ARGS(&texture_upload_heap)));


        std::vector<UINT8> texture = gen_texture(256,256,4);


        D3D12_SUBRESOURCE_DATA texture_data = {};
        texture_data.pData = &texture[0];
        texture_data.RowPitch = 256 * 4; //texture width* pixelsize(rgba)
        texture_data.SlicePitch = texture_data.RowPitch * 256; // rowpitch * TextureHeight

        UpdateSubresources(g.command_list_.Get(), g.texture_.Get(), texture_upload_heap.Get(), 0, 0, 1, &texture_data);
        g.command_list_->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(g.texture_.Get(),
                                            D3D12_RESOURCE_STATE_COPY_DEST,
                                            D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));

        //describe and create a srv for the texture
        D3D12_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
        srv_desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srv_desc.Format = texture_desc.Format;
        srv_desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        srv_desc.Texture2D.MipLevels = 1;
        g.device_->CreateShaderResourceView(g.texture_.Get(), &srv_desc, g.srv_heap_->GetCPUDescriptorHandleForHeapStart());


    }

    // Close the command list and execute it to begin the initial GPU setup.
    ThrowIfFailed(g.command_list_->Close());
    ID3D12CommandList* ppCommandLists[] = { g.command_list_.Get() };
    g.command_queue_->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
    



    //create syncronize object
    {
        ThrowIfFailed(g.device_->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&s.fence_)));
        s.fenceValue_ = 1;

        // create fence event
        s.fence_event_ = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        if (s.fence_event_ == nullptr){
            ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
        }


        // Wait for the command list to execute; we are reusing the same command 
        // list in our main loop but for now, we just want to wait for setup to 
        // complete before continuing.
        WaitForPreviousFrame(g, s);
    }

}


void 
PopulateCommandList(GraphicsContext& g, SyncronizeObejct& s) {
    
    ThrowIfFailed(g.command_allocator_->Reset());
    ThrowIfFailed(g.command_list_->Reset(g.command_allocator_.Get(), g.pipeline_state_.Get()));
    
    ID3D12DescriptorHeap* ppHeaps[] = { g.srv_heap_.Get() };


    g.command_list_->SetGraphicsRootSignature(g.root_signature_.Get());

    g.command_list_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
    g.command_list_->SetGraphicsRootDescriptorTable(0, g.srv_heap_->GetGPUDescriptorHandleForHeapStart());


    g.command_list_->RSSetViewports(1, &g.viewport_);
    g.command_list_->RSSetScissorRects(1, &g.scissor_rect_);
    
    
    // Indicate that the back buffer will be used as a render target.
    g.command_list_->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(
                                        g.render_targets_[s.frame_index_].Get(),
                                        D3D12_RESOURCE_STATE_PRESENT,
                                        D3D12_RESOURCE_STATE_RENDER_TARGET)
                                    );




    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(g.rtv_heap_->GetCPUDescriptorHandleForHeapStart(), 
                                            s.frame_index_, 
                                            g.rtv_descriptor_size_);

    g.command_list_->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
    static float ts = 0.001f;
    static int j = 0;
    // record cmd
    //float clearColor[] = { 0.0f, 0.2f , 0.4f, 1.0f };
   
    float clearColor[] = { 0.0f, 0.0f , (0.0f, 0.0f + ts * j) - (int)(0.0f, 0.0f + ts * j++) };
    spdlog::info("test color {} : ", (0.0f, 0.0f + ts * j) - (int)(0.0f, 0.0f + ts * j++));
    g.command_list_->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
    g.command_list_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    g.command_list_->IASetVertexBuffers(0, 1, &g.vertex_buffer_view_);
    g.command_list_->DrawInstanced(3, 1, 0, 0);
    // Indicate that the back buffer will now be used to present.

    g.command_list_->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(
                                        g.render_targets_[s.frame_index_].Get(), 
                                        D3D12_RESOURCE_STATE_RENDER_TARGET, 
                                        D3D12_RESOURCE_STATE_PRESENT)
                                    );



    ThrowIfFailed(g.command_list_->Close());
}


void 
WaitForPreviousFrame(GraphicsContext& g, SyncronizeObejct& s)
{
    // WAITING FOR THE FRAME TO COMPLETE BEFORE CONTINUING IS NOT BEST PRACTICE.
    // This is code implemented as such for simplicity. The D3D12HelloFrameBuffering
    // sample illustrates how to use fences for efficient resource usage and to
    // maximize GPU utilization.

    // Signal and increment the fence value.
    const UINT64 fence = s.fenceValue_;
    ThrowIfFailed(g.command_queue_->Signal(s.fence_.Get(), fence));
    s.fenceValue_++;

    // Wait until the previous frame is finished.
    if (s.fence_->GetCompletedValue() < fence)
    {
        ThrowIfFailed(s.fence_->SetEventOnCompletion(fence, s.fence_event_));
        WaitForSingleObject(s.fence_event_, INFINITE);
    }

    s.frame_index_= g.swap_chain_->GetCurrentBackBufferIndex();
}

void
GraphicManager::initialize(Application* app) {
    //load dx12 pipeline
    graphics_context_ = new GraphicsContext();
    syncronize_object_ = new SyncronizeObejct();

    UINT dxgiFactoryFlags = 0;

#if defined(_DEBUG)
    // Enable the debug layer (requires the Graphics Tools "optional feature").
    // NOTE: Enabling the debug layer after device creation will invalidate the active device.
    {
        ComPtr<ID3D12Debug> debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
        {
            debugController->EnableDebugLayer();

            // Enable additional debug layers.
            dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
        }
    }
#endif

    ComPtr<IDXGIFactory4> factory;
    ThrowIfFailed(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory)));

    //if (m_useWarpDevice)
    //if (false)
    //{
    //    ComPtr<IDXGIAdapter> warpAdapter;
    //    ThrowIfFailed(factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter)));

    //    ThrowIfFailed(D3D12CreateDevice(
    //        warpAdapter.Get(),
    //        D3D_FEATURE_LEVEL_11_0,
    //        IID_PPV_ARGS(&gdesc->device_)
    //    ));
    //}
    //else
    {
        ComPtr<IDXGIAdapter1> hardwareAdapter;
        GetHardwareAdapter(factory.Get(), &hardwareAdapter, false);

        ThrowIfFailed(D3D12CreateDevice(
            hardwareAdapter.Get(),
            D3D_FEATURE_LEVEL_11_0,
            IID_PPV_ARGS(&graphics_context_->device_)
        ));
    }

    // Describe and create the command queue.
    D3D12_COMMAND_QUEUE_DESC queue_desc = {};
    queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    ThrowIfFailed(graphics_context_->device_->CreateCommandQueue(&queue_desc, IID_PPV_ARGS(&(graphics_context_->command_queue_))));


    //create viewport temporary and scissorrect
    // 
    graphics_context_->viewport_ = {(0.0f), 0.0f, static_cast<float>(app->get_width()), static_cast<float>(app->get_height())};
    graphics_context_->scissor_rect_ = { 0, 0, static_cast<LONG>(app->get_width()), static_cast<LONG>(app->get_height()) };

    // Describe and create the swap chain.
    DXGI_SWAP_CHAIN_DESC1 swapchain_desc = {};
    swapchain_desc.BufferCount =  frame_count_;
    swapchain_desc.Width = app->get_width();
    swapchain_desc.Height = app->get_height();
    swapchain_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapchain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapchain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapchain_desc.SampleDesc.Count = 1;

    ComPtr<IDXGISwapChain1> swap_chain;
    ThrowIfFailed(factory->CreateSwapChainForHwnd(
        graphics_context_->command_queue_.Get(),        // Swap chain needs the queue so that it can force a flush on it.
        WindowsPlatform::get_HWND(),
        &swapchain_desc,
        nullptr,
        nullptr,
        &swap_chain
    ));

    // This sample does not support fullscreen transitions.
    ThrowIfFailed(factory->MakeWindowAssociation(WindowsPlatform::get_HWND(), DXGI_MWA_NO_ALT_ENTER));

    ThrowIfFailed(swap_chain.As(&graphics_context_->swap_chain_));
    syncronize_object_->frame_index_ = graphics_context_->swap_chain_->GetCurrentBackBufferIndex();

    // Create descriptor heaps.
    {
        // Describe and create a render target view (RTV) descriptor heap.
        D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
        rtvHeapDesc.NumDescriptors = frame_count_;
        rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        ThrowIfFailed(graphics_context_->device_->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&graphics_context_->rtv_heap_)));
       
        
        
        // Describe and create a shader resource view (SRV) heap for the texture.
        D3D12_DESCRIPTOR_HEAP_DESC  srv_heap_desc = {};
        srv_heap_desc.NumDescriptors = 1;
        srv_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        srv_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        ThrowIfFailed(graphics_context_->device_->CreateDescriptorHeap(&srv_heap_desc, IID_PPV_ARGS(&graphics_context_->srv_heap_)));

        
        
        graphics_context_->rtv_descriptor_size_= graphics_context_->device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    }

    // Create frame resources.
    {
        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(graphics_context_->rtv_heap_->GetCPUDescriptorHandleForHeapStart());

        // Create a RTV for each frame.
        for (UINT n = 0; n < frame_count_; n++)
        {
            ThrowIfFailed(graphics_context_->swap_chain_->GetBuffer(n, IID_PPV_ARGS(&graphics_context_->render_targets_[n])));
            graphics_context_->device_->CreateRenderTargetView(graphics_context_->render_targets_[n].Get(), nullptr, rtvHandle);
            rtvHandle.Offset(1, graphics_context_->rtv_descriptor_size_);
        }
    }

    ThrowIfFailed(graphics_context_->device_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&graphics_context_->command_allocator_)));



    load_assets(*graphics_context_, *syncronize_object_);

}


 void 
GraphicManager::render() {
     spdlog::info("frame : {}", n_frame_++);
     //record all the command we need to render the scene into the command list

     PopulateCommandList(*graphics_context_, *syncronize_object_);


     ID3D12CommandList* ppCommandLists[] = { graphics_context_->command_list_.Get() };
     graphics_context_->command_queue_->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
     
     ThrowIfFailed(graphics_context_->swap_chain_->Present(1, 0));
     WaitForPreviousFrame(*graphics_context_, *syncronize_object_);
}

 void
GraphicManager::destroy() {

     // Ensure that the GPU is no longer referencing resources that are about to be
     // cleaned up by the destructor.
     //WaitForPreviousFrame();
     WaitForPreviousFrame(*graphics_context_, *syncronize_object_);
     CloseHandle(syncronize_object_->fence_event_);
}




Buffer*
GraphicManager::make_buffer() {
    return nullptr;
}