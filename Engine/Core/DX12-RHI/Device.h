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
			HRESULT check_feature_support(D3D12_FEATURE Feature, void* pFeatureSupportData,	UINT FeatureSupportDataSize);
			HRESULT create_root_signature(MUINT node_mask, const void* buf_ptr, MUINT buf_size, ComPtr<ID3D12RootSignature>& root_sig);
			HRESULT create_graphics_pipelinestate(const D3D12_GRAPHICS_PIPELINE_STATE_DESC* p_desc, ComPtr<ID3D12PipelineState>& m_pipeline_object);
			HRESULT create_command_list(UINT nodeMask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator* pCommandAllocator, ID3D12PipelineState* pInitialState, ComPtr<ID3D12GraphicsCommandList>& m_command_list);
			HRESULT create_commit_resource(const D3D12_HEAP_PROPERTIES* pHeapProperties,
				D3D12_HEAP_FLAGS HeapFlags,
				const D3D12_RESOURCE_DESC* pDesc,
				D3D12_RESOURCE_STATES InitialResourceState,
				const D3D12_CLEAR_VALUE* pOptimizedClearValue,
				ComPtr<ID3D12Resource>& buffer			);
			HRESULT create_constant_buffer_view(D3D12_CONSTANT_BUFFER_VIEW_DESC* csv_desc, D3D12_CPU_DESCRIPTOR_HANDLE heap_cpu_handle);

		public:
			
			~Device() { m_device.Reset(); };
		};
	};
}