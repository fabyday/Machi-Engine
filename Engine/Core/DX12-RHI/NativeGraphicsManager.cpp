#include "NativeGraphicsManager.h"

using namespace Machi::NativeGraphics;

NativeGraphicsManager* NativeGraphicsManager::instance_ = nullptr;


bool NativeGraphicsManager::initialize()
{
	
	m_device = std::make_shared<Device>();
	if (!m_device->init_device()) {
		return false;
	}

	m_command_queue = std::make_shared<CommandQueue>();
	if (!m_command_queue->init(m_device)) {
		return false;
	}
	m_swapchain = std::make_shared<SwapChain>();
	if (!m_swapchain->init(m_command_queue)) {
		return false;
	}
	m_sync_manager = std::make_shared<GraphicsSyncManager>();
	if (!m_sync_manager->create(m_device, m_swapchain->get_frame_num())) {
		return false;
	}
	return true;
}