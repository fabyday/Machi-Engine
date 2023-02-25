#include "Commons.h"
#include <Graphics/graphics_defined.h>

#include "Device.h"
#include "Resouce.h"
namespace Machi {


	class DescriptorHeap {


		D3D12_DESCRIPTOR_HEAP_DESC m_desc;
		ComPtr<ID3D12DescriptorHeap> m_heap;
		D3D12_CPU_DESCRIPTOR_HANDLE m_cpu_handle_begin;
		D3D12_GPU_DESCRIPTOR_HANDLE m_gpu_handle_begin;


		MUINT m_cpu_handle_increment_size;
		MUINT m_cur_index;

		inline DescriptorHeap& setup(DescriptorHeapType type, MUINT num_descriptors, DescriptorHeapFlags flag = DescriptorHeapFlags::MACHI_DESCRIPTOR_HEAP_FLAG_NONE, MUINT nodemask = 0) {
			m_desc.Type = type;
			m_desc.NumDescriptors = num_descriptors;
			m_desc.Flags = flag;
			m_desc.NodeMask = mask;
			return *this;
		}
		inline DescriptorHeap& init(Device& device) {

			ThrowIfFailed(device->CreateDescriptorHeap(&m_desc, IID_PPV_ARGS(m_heap.GetAddressOf())));
			m_cpu_handle_begin = m_heap->GetCPUDescriptorHandleForHeapStart();
			m_gpu_handle_begin = m_heap->GetGPUDescriptorHandleForHeapStart();
			m_cpu_handle_increment_size = device->GetDescriptorHandleIncrementSize(m_desc.Type);
			m_cur_index = 0;
			return *this;

		}

		inline bool connect_view(Device& device, IResource& resource) {
			if (m_cur_index < size()) {
				resource.connect_to_heap(device, get_cpu_handle(m_cur_index++));
				return true
			}
			return false;
		}
		inline MUINT size() {
			return m_desc.NumDescriptors;
		};

		inline D3D12_CPU_DESCRIPTOR_HANDLE get_cpu_handle(MUINT index) {
			return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_cpu_handle_begin, index * m_cpu_handle_increment_size);
		};

		inline D3D12_GPU_DESCRIPTOR_HANDLE get_cpu_handle(MUINT index) {
			return CD3DX12_GPU_DESCRIPTOR_HANDLE(m_gpu_handle_begin, index * m_cpu_handle_increment_size);
		};
	};


}