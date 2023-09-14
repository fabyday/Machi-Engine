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


			inline ID3D12Device* operator->() { return m_device.Get(); };
			HRESULT create_fence(MUINT init_value, Machi::Graphics::FenceFlags flag, ComPtr<ID3D12Fence>& fence_com_ptr);
			HRESULT create_command_queue(D3D12_COMMAND_QUEUE_DESC* desc,  ComPtr<ID3D12CommandQueue>& command_queue);
		public:
			~Device() { m_device.Reset(); };
		};
	};
}