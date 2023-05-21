#pragma once
#include "Device.h"
#include "RootSignature.h"
#include "Texture.h"
#include "Buffer.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include "CommandAllocator.h"
#include "GraphicsCommand.h"
#include "Synchronizer.h"
#include <memory>
namespace Machi{

	class NativeGraphicsManager final {
	private:
		static NativeGraphicsManager* instance;
		
		bool m_is_init;
		
		Device m_device;
		SwapChain m_swapchain;

		CommandQueue m_command_queue;
		CommandAllocator m_command_allocator;
		GraphicsSyncManager sync_manager;
		class InputLayoutSpecifier;
		class RenderObject;
		bool init();
	public:

		NativeGraphicsManager& get_instance() {
			if (!instance) {
				instance = new NativeGraphicsManager();
				if (!(m_is_init = instance->init())) {
					;
				}
			}
			return *instance;
		}
		Texture* alloc_texture2d(MUINT width, MUINT height);
		Texture* alloc_texture3d(MUINT width, MUINT height, MUINT depth);
		Texture* alloc_texture1d(MUINT size);

		Buffer* alloc_buffer(MUINT byte_size);
		PipeLineState* alloc_pso();

		// handle root params
		InputLayoutSpecifier* create_input_layout();
		RenderObject* create_render_object(InputLayoutSpecifier* specifier); 


		bool render(RenderObject* object);


	};



}
