#include "Buffer.h"
#include <DX12-RHI/NativeGraphicsManager.h>
MUINT Machi::Graphics::Buffer::size()
{
	return m_data.size();
}

void Machi::Graphics::Buffer::set_native_pointer(void* p, MUINT size)
{
	memcpy_s(m_data.data(), m_data.size(), p, size);
}

void Machi::Graphics::Buffer::set_data(std::vector<char>& src)
{
	m_data.assign(src.begin(), src.end());
}

void Machi::Graphics::Buffer::set_data(void* t, MUINT size)
{
	memcpy_s(m_data.data(), m_data.size(), t, size);

}

const std::vector<char>& Machi::Graphics::Buffer::as_vector()
{
	return m_data;
}

void Machi::Graphics::Buffer::commit_data_to_gpu()
{
	auto mng = Machi::NativeGraphics::NativeGraphicsManager::get_instance();
}

void Machi::Graphics::Buffer::initialize(MUINT size)
{
	m_data.resize(size);
}
