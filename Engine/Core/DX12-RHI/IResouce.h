#pragma once
#include "Commons.h"
namespace Machi {


	namespace NativeGraphics {

		class IResource abstract {
			friend class DescriptorHeap;
		protected:
			virtual bool init() = 0;
			virtual bool copy(void* data, MUINT size) = 0;
			virtual bool connect_to_heap(Device& device, D3D12_CPU_DESCRIPTOR_HANDLE handle) = 0;
		};
	}
}