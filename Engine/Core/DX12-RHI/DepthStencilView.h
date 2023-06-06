#include "DescriptorHeap.h"
#include "Device.h"
#include "SwapChain.h"
#include <vector>
namespace Machi {


	namespace NativeGraphics {

		class DepthStencilView {
			


			std::vector<ComPtr<ID3D12Resource>> m_render_target;
		public:

			bool init(Device& device, SwapChain& swapchain, DescriptorHeap& heap) {

				D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
				rtvHeapDesc.NumDescriptors = FrameCount;
				rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
				rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
				ThrowIfFailed(m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap)));


				MUINT frame_size = swapchain.get_frame_count();
				m_render_target.resize(frame_size);
				for (int i = 0; i < frame_size; i++) {
					ThrowIfFailed(m_swapChain->GetBuffer(n, IID_PPV_ARGS(&m_renderTargets[n])));
					device->CreateRenderTargetView(m_rednerTargets)

				}
			}


		};
	}
}