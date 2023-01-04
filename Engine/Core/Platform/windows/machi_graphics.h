//MIT License 
//Copyright(c) 2022 fabyday
// 
// 
//Permission is hereby granted, free of charge, to any person
//obtaining a copy of this softwareand associated documentation
//files(the "Software"), to deal in the Software without
//restriction, including without limitation the rights to use,
//copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the
//Software is furnished to do so, subject to the following
//conditions :
//
//The above copyright noticeand this permission notice shall be
//included in all copies or substantial portions of the Software.
// 
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//OTHER DEALINGS IN THE SOFTWARE.
#pragma once
#include <Graphics/GraphicManager.h>
#include "config.h"
#include "d3d12.h"
#include "d3dx12.h"
#include "os_native.h"
#include "dxhelper.h"
#include <wrl.h> // ComPtr header
#include <shellapi.h>

#include <directxmath.h>
#include <D3Dcompiler.h>
#include <dxgi1_4.h>


#include <d3d12sdklayers.h> // for debugging

#include <DirectXMath.h>
#include <spdlog/spdlog.h>
#include <utility>
template <typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;
using namespace DirectX;
class ApplicationManager;
class GraphicsManager;


class Device;
class CommandQueue;
class SwapChain;

class GraphicsContextManager final {
	ComPtr<IDXGIFactory4> m_factory = nullptr;
	std::unique_ptr<Device> m_device_ref = nullptr;
	static std::unique_ptr<GraphicsContextManager> instance;

	Viewport m_viewport;


	friend class ApplicationManager;
	friend class GraphicsManager;
private:
	GraphicsContextManager() {

	};
	
	bool init();
public:
	bool is_valid();

	static Device& get_device() { return *(GraphicsContextManager::instance->m_device_ref); };
};

class Device final {

	ComPtr<ID3D12Device> m_device;
	friend class GraphicsContextManager;
	bool init_device(ComPtr<IDXGIFactory4> factory);
public:
	ComPtr<ID3D12Device> get_device() { return m_device; };

	

};

class CommandQueue final {
	ComPtr<ID3D12CommandQueue> m_command_queue;
	SwapChain m_swapchain;
	bool init_queue(ComPtr<ID3D12Device> device);
	bool connect_swapchian(SwapChain sc);

};

class Viewport final {
	D3D12_VIEWPORT m_viewport;
	D3D12_RECT m_scissor_rect;
	bool init_viewport(MINT width, MINT height);
};

class Buffer;
class SwapChain final {
	ComPtr<IDXGISwapChain3> swap_chain_;
	void init_swapchain(ComPtr<IDXGIFactory4> factory, MUINT frame_count_, MUINT width, MUINT height);
	bool add_resources();
	
};
class Buffer {
	enum Type {COSNTANT, };
};





class HlslShader final {
	bool m_is_precompiled;



};


