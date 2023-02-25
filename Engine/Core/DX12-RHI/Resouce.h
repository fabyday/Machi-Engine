#pragma once
#include "Commons.h"
namespace Machi {




	class IResource {

	protected:

		virtual bool connect_to_heap(Device& device, D3D12_CPU_DESCRIPTOR_HANDLE handle) = 0;
	};
}