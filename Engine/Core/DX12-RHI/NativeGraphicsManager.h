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

#include <memory>
namespace Machi{
	namespace NativeGraphics {
		class NativeGraphicsManager final {
		private:
			static NativeGraphicsManager* instance_;

			bool m_is_init;
			friend class GraphicManager;
			Device m_device;
			SwapChain m_swapchain;



			std::vector<RootSignature> m_rootsignatures;
			std::vector<DescriptorHeap> m_descriptor_heaps;
			DescriptorHeap m_rtv; //redner descriptor heap
			DescriptorHeap m_dsv; //depth stencil descriptor heap
			std::vector<PipeLineState> m_pipelines;



			CommandQueue m_command_queue;
			CommandAllocator m_command_allocator;
			GraphicsSyncManager m_sync_manager;
			class InputLayoutSpecifier;
			class RenderObject;
		public:

			bool initialize();
			static NativeGraphicsManager* get_instance() {
				if (!instance_) {
					instance_ = new NativeGraphicsManager();
				}
				return instance_;
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
	};


}
