#pragma once
#include <iostream>

#include "Device.h"
#include "Commons.h"
#include <unordered_map>

class RootParameter {



	std::unordered_map<MSTRING, int> m_mapper;
	std::vector<CD3DX12_ROOT_PARAMETER> m_root_params;


public:
	inline RootParameter& add_inline_constants(MSTRING name, MUINT size, MUINT shader_register, MUINT register_space = 0 ) {
		
		const int idx = m_root_params.size();
		m_root_params.emplace_back({}); 
		m_mapper.insert(std::make_pair<MSTRING, int>(name, idx));
		InitAsConstants(&m_root_params[idx], size, shader_register, register_space);

	}
	inline RootParameter& add_inline_constants(MUINT size, MUINT shader_register, MUINT register_space = 0) {
		const int idx = m_root_params.size();
		add_inline_constants(std::to_string(idx), size, shader_register, register_space);
	}
	inline RootParameter& add_root_constant(MUINT ) {
		m_root_params.emplace_back({}).InitAsConstants(&m_root_params[0], size, shader_register, register_space);
	}


	inline CD3DX12_ROOT_PARAMETER& operator[](const MSTRING& name) {

		return m_root_params[m_mapper.at(name)];
	}



	inline CD3DX12_ROOT_PARAMETER& operator[](const MINT index) {

		return m_root_params[index];

	}



	void* Get() {

	}


};