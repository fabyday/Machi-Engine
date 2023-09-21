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

bool Machi::NativeGraphics::NativeGraphicsManager::initialize_default_PSO()
{

	PipeLineState* ptr = new PipeLineState;
	m_pipelines.push_back(ptr);

	return false;
}

bool Machi::NativeGraphics::NativeGraphicsManager::initialize_default_root_signature()
{
	RootSignature* ptr = new RootSignature;
	m_rootsignatures.push_back(ptr);
	return true;
}

bool Machi::NativeGraphics::NativeGraphicsManager::render(std::shared_ptr<Machi::Graphics::Renderer> object)
{



	if (object == nullptr)
		return false;
	object->get_mesh();;\
	
	

	


	return true;
}
