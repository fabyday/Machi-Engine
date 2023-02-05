#include "NativeGraphicsManager.h"


bool Machi::NativeGraphicsManager::init()
{
	

	if (!m_device.init_device()) {
		return false;
	}

	if (!m_command_queue.init(m_device)) {
		return false;
	}

	if (!m_swapchain.init()) {
		return false;
	}


	return true;
}