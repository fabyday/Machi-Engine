#pragma once
#include "Commons.h"
#include <Windows.h>
#include <Platform/windows/windows_platform.h>
#include "CommandQueue.h"
#include <memory>
namespace Machi {


	class SwapChain final {

		DXGI_SWAP_CHAIN_DESC1 m_swapchain_desc;
		HWND m_target_hwnd;
		std::shared_ptr<CommandQueue> m_command_queue;
		ComPtr<IDXGISwapChain3> m_swaphain;
		MUINT m_frame_index;
		friend class NativeGraphicsManager;
		struct {
			bool Width=false;
			bool Height=false;
			bool Format=false;
			bool Stereo=false;
			bool SampleDesc=false;
			bool BufferUsage=false;
			bool BufferCount=false;
			bool Scaling=false;
			bool SwapEffect=false;
			bool AlphaMode=false;
			bool Flags=false;
			bool hwnd=false;
			bool command_queue = false;
			bool fullscreen = false;
		} ready_flag;

		bool init();

		inline SwapChain& set_command_queue(std::shared_ptr<CommandQueue> queue = NULL) {
			ready_flag.command_queue = true;
			m_command_queue = queue;
			return *this;
		}

		inline SwapChain& set_viewport(MUINT width, MUINT height) {
			ready_flag.Height =  ready_flag.Width = true;
			m_swapchain_desc.Width = width;
			m_swapchain_desc.Height = height;
			return *this;

		}

		inline MUINT get_frame_num() { return m_swapchain_desc.BufferCount; };

		inline SwapChain& set_frame_num(MUINT frame = 2) {
			ready_flag.BufferCount = true;
			m_swapchain_desc.BufferCount = frame;
			return *this;
		}
		inline SwapChain& set_hwnd(HWND hwnd = NULL) {
			ready_flag.hwnd = true;
			if (hwnd == NULL)
				m_target_hwnd = WindowsPlatform::get_HWND();
			else
				m_target_hwnd = hwnd;


			return *this;
		}
		inline SwapChain& set_foramt(ResourceFormat format = MACHI_FORMAT_R32G32B32_FLOAT) {
			ready_flag.Format = true;
			switch (format) {
				case ResourceFormat::MACHI_FORMAT_R32G32B32_FLOAT:
					m_swapchain_desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
					break;
				default:
					m_swapchain_desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
					break;

			}
			return *this;

		}


		inline SwapChain& set_buffer_usage(BufferUsage usage = MACHI_USAGE_RENDER_TARGET_OUTPUT) {
			ready_flag.BufferUsage = true;
			switch (usage)
			{
			case Machi::MACHI_CPU_ACCESS_NONE:
				break;
			case Machi::MACHI_CPU_ACCESS_DYNAMIC:
				break;
			case Machi::MACHI_CPU_ACCESS_READ_WRITE:
				break;
			case Machi::MACHI_CPU_ACCESS_SCRATCH:
				break;
			case Machi::MACHI_CPU_ACCESS_FIELD:
				break;
			case Machi::MACHI_USAGE_SHADER_INPUT:
				break;
			case Machi::MACHI_USAGE_RENDER_TARGET_OUTPUT:
				m_swapchain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				break;
			case Machi::MACHI_USAGE_BACK_BUFFER:
				break;
			case Machi::MACHI_USAGE_SHARED:
				break;
			case Machi::MACHI_USAGE_READ_ONLY:
				break;
			case Machi::MACHI_USAGE_DISCARD_ON_PRESENT:
				break;
			case Machi::MACHI_USAGE_UNORDERED_ACCESS:
				break;
			default:
				break;
			}
			return *this;

		}
		inline SwapChain& set_swap_effect(SwapEffect effect = MACHI_SWAP_EFFECT_FLIP_DISCARD) {
			ready_flag.SwapEffect= true;

			switch (effect)
			{
			case Machi::MACHI_SWAP_EFFECT_DISCARD:
				m_swapchain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
				break;
			case Machi::MACHI_SWAP_EFFECT_SEQUENTIAL:
				m_swapchain_desc.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
				break;
			case Machi::MACHI_SWAP_EFFECT_FLIP_SEQUENTIAL:
				m_swapchain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
				break;
			case Machi::MACHI_SWAP_EFFECT_FLIP_DISCARD:
				m_swapchain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
				break;
			default:
				m_swapchain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
				break;
			}
			return *this;

		}
		inline SwapChain& set_sample_type(MUINT count = 1, MUINT quality = 0) {
			ready_flag.SampleDesc = true;

			if (quality < 0)
				quality = 0;
			else if (quality > 1)
				quality = 1;

			m_swapchain_desc.SampleDesc.Count = count;
			m_swapchain_desc.SampleDesc.Quality = quality;

			return *this;
		}


		
		IDXGISwapChain3* operator->() {
			return m_swaphain.Get();
		}
	};
}