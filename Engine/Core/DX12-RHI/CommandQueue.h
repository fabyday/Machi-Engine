#pragma once
#include "Device.h"
namespace Machi {



	class CommandQueue final{
		ComPtr<ID3D12CommandQueue> m_command_queue;
		friend class NativeGraphicsManager;
		friend class SwapChain;
		bool init(Device& device);


		
		inline ID3D12CommandQueue* operator->() { return m_command_queue.Get(); };
		inline ID3D12CommandQueue* Get() { return m_command_queue.Get(); };
		bool execute_command();
	};
}