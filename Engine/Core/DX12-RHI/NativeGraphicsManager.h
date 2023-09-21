#pragma once

#include "Device.h"
#include "RootSignature.h"
#include "Texture.h"
#include "Buffer.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include "CommandAllocator.h"
#include "PipelineStateObject.h"
#include "GraphicsCommand.h"
#include "Synchronizer.h"
#include "DescriptorHeap.h"


#include <Graphics/Renderer.h>
#include <memory>


namespace Machi{
	namespace NativeGraphics {
		class NativeGraphicsManager final {
		private:
			static NativeGraphicsManager* instance_;

			bool m_is_init;
			friend class GraphicManager;
			std::shared_ptr<Device> m_device;
			std::shared_ptr<SwapChain> m_swapchain;



			std::vector<RootSignature*> m_rootsignatures;
			std::vector<DescriptorHeap*> m_descriptor_heaps;
			DescriptorHeap m_rtv; //redner descriptor heap
			DescriptorHeap m_dsv; //depth stencil descriptor heap
			std::vector<PipeLineState*> m_pipelines;



			std::shared_ptr<CommandQueue> m_command_queue;
			std::shared_ptr<CommandAllocator> m_command_allocator;
			std::shared_ptr<GraphicsSyncManager> m_sync_manager;
			class InputLayoutSpecifier;
			class RenderObject;
		public:

			bool initialize();
			bool initialize_default_PSO();
			bool initialize_default_root_signature();


			static NativeGraphicsManager* get_instance() {
				if (!instance_) {
					instance_ = new NativeGraphicsManager();
				}
				return instance_;
			}
			Texture* alloc_textureR(MUINT R);
			Texture* alloc_textureRG(MUINT R, MUINT B);
			Texture* alloc_textureRGB(MUINT R, MUINT G, MUINT B);
			Texture* alloc_textureRGBA(MUINT R, MUINT G, MUINT B, MUINT A);

			Buffer* alloc_buffer(MUINT byte_size);
			PipeLineState* alloc_pso();



			// handle root params
			InputLayoutSpecifier* create_input_layout();
			RenderObject* create_render_object(InputLayoutSpecifier* specifier);


			bool render(std::shared_ptr<Machi::Graphics::Renderer> object); //render it directly on gameview and editor view.


		};
	};


}
