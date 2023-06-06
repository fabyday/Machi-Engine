#include "Texture.h"

MUINT Machi::Graphics::Texture::size()
{
	return m_data.size();
}

void Machi::Graphics::Texture::set_native_pointer(void* p, MUINT size)
{

}

void Machi::Graphics::Texture::set_data(std::vector<char>& src)
{
	m_data.assign(src.begin(), src.end());
}

void Machi::Graphics::Texture::set_data(void* t, MUINT size)
{
	memcpy_s(m_data.data(), m_data.size(), t, size);
}

const std::vector<char>& Machi::Graphics::Texture::as_vector()
{
	return m_data;
}

void Machi::Graphics::Texture::commit_data_to_gpu()
{
}

void Machi::Graphics::Texture::initialize(MUINT size)
{
	m_data.resize(size);
}
