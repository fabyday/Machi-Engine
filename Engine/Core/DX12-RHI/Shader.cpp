#include "Shader.h"
using namespace Machi::Graphics;
using namespace Machi::NativeGraphics;
#include "dxhelper.h"
void Shader::create()
{

	{
#if defined(_DEBUG)
		// Enable better shader debugging with the graphics debugging tools.
		UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		UINT compileFlags = 0;
#endif			

		std::string ch_entry_name;
		ch_entry_name.assign(m_entry_name.begin(), m_entry_name.end());

		if (m_content_is_file) {
			switch (m_type) {
			case MACHI_VERTEX_SHADER:
				ThrowIfFailed(D3DCompileFromFile(m_content.c_str(), nullptr, nullptr, ch_entry_name.c_str(), "vs_5_0", compileFlags, 0, &m_shader, nullptr));
				break;
			case MACHI_PIXEL_SHADER:
				ThrowIfFailed(D3DCompileFromFile(m_content.c_str(), nullptr, nullptr, ch_entry_name.c_str(), "ps_5_0", compileFlags, 0, &m_shader, nullptr));
				break;
			}
		}
		else {
			switch (m_type) {
			case MACHI_VERTEX_SHADER:
				ThrowIfFailed(D3DCompile(m_content.c_str(), m_content.size(), nullptr, nullptr, nullptr, ch_entry_name.c_str(), "vs_5_0", 0, 0, &m_shader, nullptr));
				break;
			case MACHI_PIXEL_SHADER:
				ThrowIfFailed(D3DCompile(m_content.c_str(), m_content.size(), nullptr, nullptr, nullptr, ch_entry_name.c_str(), "ps_5_0", 0, 0, &m_shader, nullptr));
				break;
			}
		}

		// Define the vertex input layout.
	}
}