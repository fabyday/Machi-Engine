#pragma once
#include <Graphics/graphics_defined.h>
#include "Commons.h"
#include "native_format_converter.h"
#include "Device.h"
#include "IResouce.h"
namespace Machi {

	namespace NativeGraphics {

		class DescriptorHeap {


			D3D12_DESCRIPTOR_HEAP_DESC m_desc;
			ComPtr<ID3D12DescriptorHeap> m_heap;
			D3D12_CPU_DESCRIPTOR_HANDLE m_cpu_handle_begin;
			D3D12_GPU_DESCRIPTOR_HANDLE m_gpu_handle_begin;


			MUINT m_cpu_handle_increment_size;
			MUINT m_cur_index;
			bool m_is_init = false;

			inline DescriptorHeap& add_setup(Machi::Graphics::DescriptorHeapType type, MUINT num_descriptors, Machi::Graphics::DescriptorHeapFlags flag = Machi::Graphics::DescriptorHeapFlags::MACHI_DESCRIPTOR_HEAP_FLAG_NONE, MUINT nodemask = 0) {
				m_desc.Type = descriptor_heap_type_convert(type);
				m_desc.NumDescriptors = num_descriptors;
				m_desc.Flags = descriptor_heap_flag_convert(flag);
				m_desc.NodeMask = nodemask;
				return *this;
			}

			DescriptorHeap& init(Device& device);
			inline bool is_init() { return m_is_init; };
			inline bool connect_view(std::shared_ptr<Device> device, std::shared_ptr<IResource> resource) {
				if (m_cur_index < size()) {
					resource->connect_to_heap(device, get_cpu_handle(m_cur_index++));
					return true;
				}
				return false;
			}
			inline MUINT size() {
				return m_desc.NumDescriptors;
			};

			inline D3D12_CPU_DESCRIPTOR_HANDLE get_cpu_handle(MUINT index) {
				return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_cpu_handle_begin, index * m_cpu_handle_increment_size);
			};

			inline D3D12_GPU_DESCRIPTOR_HANDLE get_gpu_handle(MUINT index) {
				return CD3DX12_GPU_DESCRIPTOR_HANDLE(m_gpu_handle_begin, index * m_cpu_handle_increment_size);
			};
		};
	}

}