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

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")



template <typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;



typedef struct Buffer {
    template <typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;


    ComPtr<ID3D12Resource> buffer_;
    Buffer() {};

} Buffer;

typedef struct BufferView {
    D3D12_VERTEX_BUFFER_VIEW buffer_view_;


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

typedef struct GraphcisDesc{
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
}GraphcisContext;


 void
GraphicManager::initialize(Application* app) {
    //load dx12 pipeline
    GraphcisContext* gdesc = new GraphcisContext();
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
            IID_PPV_ARGS(&gdesc->device_)
        ));
    }

    // Describe and create the command queue.
    D3D12_COMMAND_QUEUE_DESC queue_desc = {};
    queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    ThrowIfFailed(gdesc->device_->CreateCommandQueue(&queue_desc, IID_PPV_ARGS(&(gdesc->command_queue_))));

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
        gdesc->command_queue_.Get(),        // Swap chain needs the queue so that it can force a flush on it.
        WindowsPlatform::get_HWND(),
        &swapchain_desc,
        nullptr,
        nullptr,
        &swap_chain
    ));

    // This sample does not support fullscreen transitions.
    ThrowIfFailed(factory->MakeWindowAssociation(WindowsPlatform::get_HWND(), DXGI_MWA_NO_ALT_ENTER));

    ThrowIfFailed(swap_chain.As(&gdesc->swap_chain_));
    syncronize_object_->frame_index_ = gdesc->swap_chain_->GetCurrentBackBufferIndex();

    // Create descriptor heaps.
    {
        // Describe and create a render target view (RTV) descriptor heap.
        D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
        rtvHeapDesc.NumDescriptors = frame_count_;
        rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        ThrowIfFailed(gdesc->device_->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&gdesc->rtv_heap_)));

        gdesc->rtv_descriptor_size_= gdesc->device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    }

    // Create frame resources.
    {
        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(gdesc->rtv_heap_->GetCPUDescriptorHandleForHeapStart());

        // Create a RTV for each frame.
        for (UINT n = 0; n < frame_count_; n++)
        {
            ThrowIfFailed(gdesc->swap_chain_->GetBuffer(n, IID_PPV_ARGS(&gdesc->render_targets_[n])));
            gdesc->device_->CreateRenderTargetView(gdesc->render_targets_[n].Get(), nullptr, rtvHandle);
            rtvHandle.Offset(1, gdesc->rtv_descriptor_size_);
        }
    }

    ThrowIfFailed(gdesc->device_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&gdesc->command_allocator_)));



}


 void 
GraphicManager::render() {

}

 void
GraphicManager::destroy() {

}




bool GraphicManager::regist_renderer()
{
    return false;
}

Buffer*
GraphicManager::make_buffer() {
    return nullptr;
}