#include "Commons.h"
#include "Resouce.h"
#include <vector>
#include <utility>
namespace Machi {
	class Buffer : public Machi::IResource {
		friend class DescriptorHeap;
		friend class NativeGraphicsManager;

		D3D12_RESOURCE_DESC m_desc;
		ComPtr<ID3D12Resource> m_buffer;
		
		// real data
		void* m_data = nullptr;

		//size is byte size
		MUINT m_buffer_size;
		Buffer& set_size(MUINT size) { m_buffer_size = size; };

		bool init(Device& device) {
			HRESULT hr = device->CreateCommittedResource(
				&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
				D3D12_HEAP_FLAG_NONE,
				&CD3DX12_RESOURCE_DESC::Buffer(m_buffer_size),
				D3D12_RESOURCE_STATE_COPY_DEST, nullptr,
				IID_PPV_ARGS(&m_buffer));
			if (FAILED(hr));
			m_data = reinterpret_cast<void*>(new MUINT[m_buffer_size]);

			CD3DX12_RANGE read_range(0, 0);
			m_buffer->Map(0, &read_range, reinterpret_cast<void**>(m_data));
			
			return true;


		};
	protected:

		virtual bool connect_to_heap(Device& device, D3D12_CPU_DESCRIPTOR_HANDLE heap_cpu_handle)  {

			D3D12_CONSTANT_BUFFER_VIEW_DESC buf_view_desc;
			buf_view_desc.BufferLocation = m_buffer->GetGPUVirtualAddress();
			buf_view_desc.SizeInBytes = m_buffer_size;
			device->CreateConstantBufferView(&buf_view_desc, heap_cpu_handle);

			return true;
		};


	public : 
		bool copy(void* src, MUINT size) {
			bool err;
			if ((err = memcpy_s(m_data, m_buffer_size, src, size))== 0)
				return true;
			return false;
		}


	};
}