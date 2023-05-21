#include <memory>

#include "Commons.h"
#include "CommandQueue.h"
#include "SwapChain.h"
namespace Machi {



	class GraphicsSyncManager {


		friend class NativeGraphicsManager;



		// Synchronization objects.
		UINT m_frame_index;
		HANDLE m_fence_event;
		ComPtr<ID3D12Fence> m_fence;
		std::unique_ptr<UINT64[]> m_fence_value;
		MUINT64 m_fence_size;

		bool create(Device& device, MUINT64 fence_size) {
			ThrowIfFailed(device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)));
			std::make_unique<UINT64[]>(m_fence_size);
			for (int i = 0; i < m_fence_size; i++)
				m_fence_value[i] = 1;
			m_fence_size = fence_size;

			// Create an event handle to use for frame synchronization.
			m_fence_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
			if (m_fence_event == nullptr)
			{
				ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
			}


			return true;
		}

		void wait_gpu(CommandQueue& queue);

		void next_frame(CommandQueue& queue);

	};
}