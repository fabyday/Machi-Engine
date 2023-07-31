#include "SwapChain.h"
#include <iostream>
using namespace Machi::NativeGraphics;
#include "dxhelper.h"
bool SwapChain::init(std::shared_ptr<CommandQueue> cmd_queue)
{

	// Describe and create the swap chain.
	if (!(ready_flag.Width && ready_flag.Height))
		set_viewport(1920, 1080);
	if (!ready_flag.BufferCount)
		set_frame_num();
	if (!ready_flag.hwnd)
		set_hwnd();
	if (!ready_flag.Format)
		set_foramt();
	if (!ready_flag.BufferUsage)
		set_buffer_usage();
	if (!ready_flag.SwapEffect)
		set_swap_effect();
	if (!ready_flag.SampleDesc)
		set_sample_type();

	UINT dxgiFactoryFlags = 0;
	ComPtr<IDXGIFactory4> factory = nullptr;

	try {
		ThrowIfFailed(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory)));
	}
	catch (HrException& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}


	ComPtr<IDXGISwapChain1> swapchain;
	try {

		ThrowIfFailed(factory->CreateSwapChainForHwnd(
			m_command_queue->Get(),        // Swap chain needs the queue so that it can force a flush on it.
			m_target_hwnd,
			&m_swapchain_desc,
			nullptr,
			nullptr,
			&swapchain
		));


		// This sample does not support fullscreen transitions.
		ThrowIfFailed(factory->MakeWindowAssociation(m_target_hwnd, DXGI_MWA_NO_ALT_ENTER));

		ThrowIfFailed(swapchain.As(&m_swaphain));
		m_frame_index = m_swaphain->GetCurrentBackBufferIndex();

	}
	catch (HrException& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}

	return true;


}
