#include "Commons.h"
#include <variant>
#include <IO/read_file.h>
namespace Machi {
	class Shader {
		//ComPtr<D3D12_SHADER_BYTECODE> m_shader;
		ComPtr<ID3DBlob> m_shader;
		friend class PipeLineState;

		ShaderType m_type;
		bool m_content_is_file;
		MSTRING m_content;
		MSTRING m_entry_name;


		bool m_is_compiled;

		Shader& set_shader_type(ShaderType type) {
			m_type = type;
			return *this;
		}

		Shader& set_function_from_str(MSTRING& str, MSTRING& entry_name) {
			m_content = str;
			m_entry_name = entry_name;
			m_content_is_file = false;
			return *this;
		};


		Shader& set_function_from_file(MSTRING& filename, MSTRING& entry_name) {
			//read_str_from_file(filename, m_content);
			m_content_is_file = true;
			m_entry_name = entry_name;
			m_content = filename;

		}

		inline bool is_valid() {
			return m_is_compiled;
		}

		void create();

		D3D12_SHADER_BYTECODE Get() {
			if (!m_is_compiled) {

				return  CD3DX12_SHADER_BYTECODE(m_shader.Get());
			}
			return CD3DX12_SHADER_BYTECODE(nullptr);
		}


	};
}