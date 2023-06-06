#pragma once 
#include <Graphics/graphics_defined.h>


namespace Machi {
	namespace NativeGraphics {
		struct pipline_desc {
			Machi::Graphics::VertexShaderInputSemantics m_semantic_name;
			Machi::Graphics::InputSlot m_input_slot;
			Machi::Graphics::ShaderInputFormat m_format;
			Machi::Graphics::ShaderInputType m_shader_input_type;
			MUINT m_aligned_offset;
		};

	}
}