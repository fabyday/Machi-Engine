#include "NativeGraphicsManager.h"

using namespace Machi::NativeGraphics;

NativeGraphicsManager* NativeGraphicsManager::instance_ = nullptr;


bool NativeGraphicsManager::initialize()
{
	

	if (!m_device->init_device()) {
		return false;
	}

	if (!m_command_queue->init(m_device)) {
		return false;
	}

	if (!m_swapchain->init(m_command_queue)) {
		return false;
	}

	if (!m_sync_manager->create(m_device, m_swapchain->get_frame_num())) {
		return false;
	}
	return true;
}