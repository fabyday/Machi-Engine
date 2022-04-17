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
    ComPtr<ID3D12PipelineState> pipeline_state_;
    ComPtr<ID3D12GraphicsCommandList> command_list_;
    UINT rtv_descriptor_size_;
}GraphicsContext;


static void load_assets(GraphicsContext& g, SyncronizeObejct& s) {
    
//create command list
    ThrowIfFailed(g.device_->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, g.command_allocator_.Get(), nullptr, IID_PPV_ARGS(&g.command_list_)));

    // recording state(must be closed)
    ThrowIfFailed(g.command_list_->Close());

    //create syncronize object
    {
        ThrowIfFailed(g.device_->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&s.fence_)));
        s.fenceValue_ = 1;

        // create fence event
        s.fence_event_ = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        if (s.fence_event_){
            ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
        }
    }

}


void 
PopulateCommandList(GraphicsContext& g, SyncronizeObejct& s) {
    
    ThrowIfFailed(g.command_allocator_->Reset());
    ThrowIfFailed(g.command_list_->Reset(g.command_allocator_.Get(), g.pipeline_state_.Get()));
    g.command_list_->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(
                                        g.render_targets_[s.frame_index_].Get(), 
                                        D3D12_RESOURCE_STATE_PRESENT, 
                                        D3D12_RESOURCE_STATE_RENDER_TARGET)
                                    );


    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(g.rtv_heap_->GetCPUDescriptorHandleForHeapStart(), 
                                            s.frame_index_, 
                                            g.rtv_descriptor_size_);



    const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
    g.command_list_->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

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


    //
    //
    //
    // Create the command list.
    ThrowIfFailed(graphics_context_->device_->CreateCommandList(
                    0, D3D12_COMMAND_LIST_TYPE_DIRECT, 
                    graphics_context_->command_allocator_.Get(), nullptr, 
                    IID_PPV_ARGS(&graphics_context_->command_list_))
                );

    // Command lists are created in the recording state, but there is nothing
    // to record yet. The main loop expects it to be closed, so close it now.
    ThrowIfFailed(graphics_context_->command_list_->Close());

    // Create synchronization objects.
    {
        ThrowIfFailed(graphics_context_->device_->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&syncronize_object_->fence_)));
        syncronize_object_->fenceValue_= 1;

        // Create an event handle to use for frame synchronization.
        syncronize_object_->fence_event_ = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        if (syncronize_object_->fence_event_ == nullptr)
        {
            ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
        }
    }
   

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