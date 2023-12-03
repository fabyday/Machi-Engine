#pragma once
#include "Commons.h"
#include "Device.h"

namespace Machi {


	namespace NativeGraphics {

		class IResource abstract {
			friend class DescriptorHeap;
		public:
			//virtual ~IResource() {};  // 가상 소멸자의 선언


		protected:
			virtual bool init(std::shared_ptr<Device> device) = 0;
			virtual bool copy(void* data, MUINT size) = 0;
			virtual bool connect_to_heap(std::shared_ptr<Device> device, D3D12_CPU_DESCRIPTOR_HANDLE handle) = 0;
		};
	}
}