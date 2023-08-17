#include "Device.h"
#include <iostream>
#include "dxhelper.h"

#include "native_format_converter.h"
using namespace Machi::NativeGraphics;
bool Device::init_device(bool debug_mode)
{
	UINT dxgiFactoryFlags = 0;
	ComPtr<IDXGIFactory4> factory = nullptr;

#if defined(_DEBUG)
	// Enable the debug layer (requires the Graphics Tools "optional feature").
	// NOTE: Enabling the debug layer after device creation will invalidate the active device.
	{
		ComPtr<ID3D12Debug> debugController;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();

			// Enable additional debug layers.
			dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
		}
	}
#else
	if (debug_mode) {
		ComPtr<ID3D12Debug> debugController;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();

			// Enable additional debug layers.
			dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
		}
	}
#endif

	try {
		ThrowIfFailed(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory)));
	}
	catch (HrException& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}



	try {

	ComPtr<IDXGIAdapter1> hardwareAdapter;
	GetHardwareAdapter(factory.Get(), &hardwareAdapter, true);

	ThrowIfFailed(D3D12CreateDevice(
		hardwareAdapter.Get(),
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&m_device)
	));
	}
	catch (HrException& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}



	return true;
}

HRESULT 
Device::create_fence(MUINT init_value, Machi::Graphics::FenceFlags flag, ComPtr<ID3D12Fence> fence_com_ptr) {
	
	return m_device->CreateFence(init_value, fence_flag_convert(flag), IID_PPV_ARGS(&fence_com_ptr));
}
HRESULT 
Device::create_command_queue(D3D12_COMMAND_QUEUE_DESC* desc, ComPtr<ID3D12CommandQueue> command_queue) {
	return m_device->CreateCommandQueue(desc, IID_PPV_ARGS(&command_queue));
}
