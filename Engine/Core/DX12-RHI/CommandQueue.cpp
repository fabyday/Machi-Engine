#include "CommandQueue.h"
#include <iostream>
bool Machi::CommandQueue::init(Device& device)
{
    // Describe and create the command queue.
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    try {
    ThrowIfFailed(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_command_queue)));

    }
    catch (HrException& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
	return true;
}
