#pragma once
#include "Device.h"
#include <iostream>
namespace Machi {

	namespace NativeGraphics {

		class CommandQueue final {
			ComPtr<ID3D12CommandQueue> m_command_queue;
			friend class NativeGraphicsManager;
			friend class SwapChain;
			friend class GraphicsSyncManager;
			bool init(std::shared_ptr<Device> device);



			inline ID3D12CommandQueue* operator->() { return m_command_queue.Get(); };
			inline ID3D12CommandQueue* Get() { 
				std::cout << m_command_queue.Get() << std::endl;
				return m_command_queue.Get(); 
			
			};
			bool execute_command();
		};
	}
}