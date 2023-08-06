#pragma once
#include <memory>

#include "Commons.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include <vector>
namespace Machi {

	namespace NativeGraphics {

		class GraphicsSyncManager {


			friend class NativeGraphicsManager;



			// Synchronization objects.
			UINT m_frame_index;
			HANDLE m_fence_event;
			ComPtr<ID3D12Fence> m_fence;
			std::vector<UINT64> m_fence_value;
			MUINT64 m_fence_size;

			bool create(std::shared_ptr<Device> device, MUINT64 fence_size);

			void wait_gpu(CommandQueue& queue, MUINT frame_index);

			void next_frame(CommandQueue& queue, SwapChain& swapchain);

		};
	};
}