#include "DescriptorHeap.h"
#include "dxhelper.h"
using namespace Machi::NativeGraphics;
inline DescriptorHeap& DescriptorHeap::init(Device& device) {

	ThrowIfFailed(device->CreateDescriptorHeap(&m_desc, IID_PPV_ARGS(m_heap.GetAddressOf())));
	m_cpu_handle_begin = m_heap->GetCPUDescriptorHandleForHeapStart();
	m_gpu_handle_begin = m_heap->GetGPUDescriptorHandleForHeapStart();
	m_cpu_handle_increment_size = device->GetDescriptorHandleIncrementSize(m_desc.Type);
	m_cur_index = 0;

	m_is_init = true;

	return *this;

}