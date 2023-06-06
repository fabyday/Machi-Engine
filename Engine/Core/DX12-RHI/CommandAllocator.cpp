#include "CommandAllocator.h"
#include <iostream>
using namespace Machi::NativeGraphics;
#include "dxhelper.h"


bool CommandAllocator::create(Device& device){
	D3D12_COMMAND_LIST_TYPE type;
	switch (m_type)
	{
	case CommandAllocator::MACHI_COMMAND_LIST_TYPE_DIRECT:
		type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		break;
	case CommandAllocator::MACHI_COMMAND_LIST_TYPE_BUNDLE:
		type = D3D12_COMMAND_LIST_TYPE_BUNDLE;
		break;
	case CommandAllocator::MACHI_COMMAND_LIST_TYPE_COMPUTE:
		type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
		break;
	case CommandAllocator::MACHI_COMMAND_LIST_TYPE_COPY:
		type = D3D12_COMMAND_LIST_TYPE_COPY;
		break;
	case CommandAllocator::MACHI_COMMAND_LIST_TYPE_VIDEO_DECODE:
		type = D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE;
		break;
	case CommandAllocator::MACHI_COMMAND_LIST_TYPE_VIDEO_PROCESS:
		type = D3D12_COMMAND_LIST_TYPE_VIDEO_PROCESS;
		break;
	case CommandAllocator::MACHI_COMMAND_LIST_TYPE_VIDEO_ENCODE:
		type = D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE;
		break;
	default:
		type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		break;
	}

	try {
		ThrowIfFailed(device->CreateCommandAllocator(type, IID_PPV_ARGS(&m_command_allocator)));
	}
	catch (HrException& e) {
		std::cout << e.what() << std::endl;
	}

	return false;
}
