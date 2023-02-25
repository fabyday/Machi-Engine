
#include "Commons.h"

namespace Machi {




	class Device final {
	private:
		ComPtr<ID3D12Device> m_device;

		friend class RootSignature;
		friend class NativeGraphicsManager;
		friend class CommandQueue;
		friend class SwapChain;
		friend class CommandAllocator;
		friend class Buffer;
		friend class Texture;
		friend class GraphicsSyncManager;
		bool m_is_valid_device = false;


		bool init_device(bool debug_mode = false);

		inline bool is_valid() { return m_is_valid_device; }

		~Device() { m_device.Reset(); };
		inline ID3D12Device* operator->() { return m_device.Get(); };


	};
}