#pragma once
#include "Commons.h"
#include <Graphics/graphics_defined.h>
#include <Logger/Logger.h>
namespace Machi {


	namespace NativeGraphics {

		class Device final {
		private:
			ComPtr<ID3D12Device> m_device;
			friend class PipeLineState;
			friend class RootSignature;
			friend class NativeGraphicsManager;
			friend class CommandQueue;
			friend class SwapChain;
			friend class CommandAllocator;
			friend class Buffer;
			friend class Texture;
			friend class PipeLineState;
			friend class GraphicsSyncManager;
			friend class DescriptorHeap;
			bool m_is_valid_device = false;

			bool init_device(bool debug_mode = false);

			inline bool is_valid() { return m_is_valid_device; }

			friend class CommandList;
			inline ID3D12Device* operator->() { return m_device.Get(); };
			HRESULT create_fence(MUINT init_value, Machi::Graphics::FenceFlags flag, ComPtr<ID3D12Fence>& fence_com_ptr);
			HRESULT create_command_queue(D3D12_COMMAND_QUEUE_DESC* desc,  ComPtr<ID3D12CommandQueue>& command_queue);
			HRESULT create_command_list(UINT nodeMask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator* pCommandAllocator, ID3D12PipelineState* pInitialState, ComPtr<ID3D12GraphicsCommandList>& m_command_list);
			HRESULT check_feature_support(D3D12_FEATURE Feature, void* pFeatureSupportData,	UINT FeatureSupportDataSize);
			HRESULT create_root_signature(MUINT node_mask, const void* buf_ptr, MUINT buf_size, ComPtr<ID3D12RootSignature>& root_sig);
			HRESULT create_graphics_pipelinestate(const D3D12_GRAPHICS_PIPELINE_STATE_DESC* p_desc, ComPtr<ID3D12PipelineState>& m_pipeline_object);
			HRESULT create_commit_resource(Machi::Graphics::HeapType heapprop, D3D12_HEAP_FLAGS HeapFlags, MUINT buffer_size, D3D12_RESOURCE_STATES InitialResourceState, const D3D12_CLEAR_VALUE* pOptimizedClearValue, ComPtr<ID3D12Resource>& buffer);
			void create_constant_buffer_view(D3D12_CONSTANT_BUFFER_VIEW_DESC* csv_desc, D3D12_CPU_DESCRIPTOR_HANDLE heap_cpu_handle);





			//create view
			//m_device->CreateDepthStencilView;
			void create_depth_stencil_view();
			void create_render_target_view();

			//m_device->CopyDescriptors;
			void copy_descriptors();
			//m_device->CreateUnorderedAccessView;
			//m_device->CreateShaderResourceView;
			
			//m_device->CopyDescriptorsSimple;
			void copy_descriptors_simple();
			
			//m_device->CreateCommandAllocator;
			HRESULT create_command_allocator(D3D12_COMMAND_LIST_TYPE type, std::shared_ptr<CommandAllocator> allocator);
			
			//m_device->CreateCommandSignature;
			//HRESULT create_command_signature(D312_COMMAND_SIGNATURE_DESC* pdesc, std::shared_ptr<RootSignature> root_ptr, std::shared_ptr<CommandSignature> command_signature);

			
			//m_device->CreateComputePipelineState;
			HRESULT create_compute_pipelinestate();
			
			
			//m_device->CreateHeap;
			//HRESULT create_heap(D3D12_HEAP_DESC* pdesc, Heap)
			
			//m_device->CreatePlacedResource;
			
			//m_device->CreateQueryHeap;
			
			//m_device->CreateReservedResource;
			
			//m_device->CreateSampler;
			
			
			//m_device->CreateSharedHandle;
			
			
			//m_device->Evict;
			
			//m_device->GetAdapterLuid;
			
			//m_device->GetCopyableFootprints;
			
			//m_device->GetCustomHeapProperties;
			
			//m_device->GetDescriptorHandleIncrementSize;
			
			//m_device->GetDeviceRemovedReason;
			
			//m_device->GetNodeCount;
			
			//m_device->GetPrivateData;
			
			//m_device->GetResourceAllocationInfo;
			
			//m_device->GetResourceTiling;
			
			//m_device->MakeResident;
			
			//m_device->OpenSharedHandle;
			
			//m_device->OpenSharedHandleByName;
			
			//m_device->QueryInterface;

			//m_device->Release;
			// 
			//m_device->SetName;
			void set_name(MSTRING name);
			
			//m_device->SetPrivateData;
			HRESULT set_private_data();
			//m_device->SetPrivateDataInterface;
			HRESULT set_private_data_interaface();
			
			//m_device->SetStablePowerState;
			HRESULT set_stable_power_state();
			

			// heap 
			//m_device->CreateDescriptorHeap;
			HRESULT create_descriptor_heap();







		public:
			
			~Device() { m_device.Reset(); };
		};
	};
}