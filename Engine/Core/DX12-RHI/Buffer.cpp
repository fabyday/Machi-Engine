#include "Buffer.h"


using namespace Machi::NativeGraphics;


bool Buffer::copy(void* data, MUINT size, bool unmap_flag = true) {
	UINT8* p_data_begin;
	CD3DX12_RANGE readRange(0, 0);        // We do not intend to read from this resource on the CPU.
	ThrowIfFailed(m_buffer->Map(0, &readRange, reinterpret_cast<void**>(&p_data_begin)));
	memcpy(p_data_begin, data, size);
	m_buffer->Unmap(0, nullptr);
}