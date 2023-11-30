#include "CommandList.h"

using namespace Machi::NativeGraphics;

void 
CommandList::initialize(std::shared_ptr<Device> device, std::shared_ptr<CommandAllocator> command_allocator, std::shared_ptr<PipeLineState> pipeline_object) {

		HRESULT res = device->create_command_list(0, D3D12_COMMAND_LIST_TYPE_DIRECT, command_allocator->Get(), pipeline_object->Get(), m_command_list);
		m_command_list->Close();
}
