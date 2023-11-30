#include "Commons.h"
#include "IResouce.h"
#include <vector>
#include <utility>
namespace Machi {
	namespace NativeGraphics {
		class Buffer : public IResource {
			friend class DescriptorHeap;
			friend class NativeGraphicsManager;

			D3D12_RESOURCE_DESC m_desc;
			ComPtr<ID3D12Resource> m_buffer;
			

			// real data
			void* m_data = nullptr;
			bool m_is_init = false;
			//size is byte size
			MUINT m_buffer_size; // buf unit size is byte.
			Machi::Graphics::HeapType m_heap_type;
			struct {


				

			} ;



			Buffer& set_size(MUINT size) { m_buffer_size = size; };
			Buffer& set_heap_type(Machi::Graphics::HeapType t) {
				m_heap_type = t;
			};

			virtual bool init(std::shared_ptr<Device> device) {
				
				HRESULT hr = device->create_commit_resource(
					&CD3DX12_HEAP_PROPERTIES(heap_type_convert(m_heap_type)),
					D3D12_HEAP_FLAG_NONE,
					&CD3DX12_RESOURCE_DESC::Buffer(m_buffer_size),
					D3D12_RESOURCE_STATE_COPY_DEST, nullptr,
					m_buffer);
				
				if (FAILED(hr))
					return false;
				
				m_data = reinterpret_cast<void*>(new char[m_buffer_size]);

				CD3DX12_RANGE read_range(0, 0);
				m_buffer->Map(0, &read_range, reinterpret_cast<void**>(m_data));
				
				m_is_init = true;
				return true;


			};
		protected:

			virtual bool connect_to_heap(std::shared_ptr<Device> device, D3D12_CPU_DESCRIPTOR_HANDLE heap_cpu_handle) {

				D3D12_CONSTANT_BUFFER_VIEW_DESC buf_view_desc;
				buf_view_desc.BufferLocation = m_buffer->GetGPUVirtualAddress();
				buf_view_desc.SizeInBytes = m_buffer_size;


				device->create_constant_buffer_view(&buf_view_desc, heap_cpu_handle);
				//device->CreateConstantBufferView(&buf_view_desc, heap_cpu_handle);

				return true;
			};


		public:
			virtual bool copy(void* data, MUINT size, bool unmap_flag = true);


		};
	};
}