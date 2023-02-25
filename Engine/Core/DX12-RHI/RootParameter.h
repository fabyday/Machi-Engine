#pragma once
#include <iostream>
#include <Graphics/graphics_defined.h>
#include "Device.h"
#include "Commons.h"
#include <unordered_map>
#include <utility>
namespace Machi {
	class RootParameter {



		std::unordered_map<MSTRING, int> m_mapper;
		std::vector<CD3DX12_ROOT_PARAMETER> m_root_params;


	public:
		inline MINT size() {
			return m_root_params.size();
		}
		inline RootParameter& add_inline_constants(MSTRING name, MUINT size, MUINT shader_register, MUINT register_space = 0, ShaderVisibility visibility = MACHI_SHADER_VISIBILITY_ALL) {

			const int idx = m_root_params.size();
			m_mapper.insert(std::make_pair<MSTRING, int>(name, idx));
			m_root_params.emplace_back({});
			m_root_params[idx].InitAsConstants(size, shader_register, register_space);


			return *this;
		}



		inline RootParameter& add_inline_constants(MUINT size, MUINT shader_register, MUINT register_space = 0, ShaderVisibility visibility = MACHI_SHADER_VISIBILITY_ALL) {
			const int idx = m_root_params.size();
			add_inline_constants(std::to_string(idx), size, shader_register, register_space, visibility);
			return *this;
		}
		inline RootParameter& add_root_descriptor_table(const std::vector<SignatureContextElements>& types, ShaderVisibility visibility = MACHI_SHADER_VISIBILITY_ALL) {
			assert(types.size() > 0 && "types vector length is too short.");
			if (types.size() == 0)
				return *this;

			const int size = types.size();
			std::vector<D3D12_DESCRIPTOR_RANGE> desc_range;
			desc_range.reserve(size);

			int desc_idx = 0;
			for (int i = 0; i < size; i++) {
				//checking same types SRV, CBV, UAV, Sampler
				int cur_type = types[i];
				int num_same_type = 1;
				for (int j = i + 1; j < size; j++) {
					if (types[j] != cur_type) {
						i = j - 1;
						break;
					}
					num_same_type++;
				}

				// description
				desc_range.emplace_back();
				switch (cur_type) {
				case SignatureContextElements::MACHI_TABLE_CONSTANT_BUFFER_VIEW_DESCRIPTOR:
					desc_range[desc_idx].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
				case SignatureContextElements::MACHI_TABLE_SHADER_RESOURCE_VIEW_DESCRIPTOR:
					desc_range[desc_idx].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
				case SignatureContextElements::MACHI_TABLE_UNORDERED_ACCESS_VIEW_DESCRIPTOR:
					desc_range[desc_idx].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
				case SignatureContextElements::MACHI_TABLE_SAMPLER:
					desc_range[desc_idx].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
				}
				desc_range[desc_idx].NumDescriptors;
				desc_range[desc_idx].BaseShaderRegister;
				desc_range[desc_idx].OffsetInDescriptorsFromTableStart;
				desc_range[desc_idx].RegisterSpace;
				desc_idx++;
			}

			const int idx = m_root_params.size();
			m_root_params.emplace_back();
			m_root_params[idx].InitAsDescriptorTable(desc_range.size(), (desc_range.data()), visibility);

			return *this;
		}


		inline RootParameter& add_inline_srv(MUINT size, MUINT shader_register, MUINT register_space = 0, ShaderVisibility visibility = MACHI_SHADER_VISIBILITY_ALL) {
			const int idx = m_root_params.size();
			m_root_params.emplace_back();
			m_root_params[idx].InitAsShaderResourceView(shader_register, register_space, visibility);

			return *this;
		}

		inline RootParameter& add_inline_uav(MUINT size, MUINT shader_register, MUINT register_space = 0, ShaderVisibility visibility = MACHI_SHADER_VISIBILITY_ALL) {
			const int idx = m_root_params.size();
			m_root_params.emplace_back();
			m_root_params[idx].InitAsUnorderedAccessView;

			return *this;
		}


		inline RootParameter& add_inline_cbv(MUINT size, MUINT shader_register, MUINT register_space = 0, ShaderVisibility visibility = MACHI_SHADER_VISIBILITY_ALL) {
			const int idx = m_root_params.size();
			m_root_params.emplace_back();
			m_root_params[idx].InitAsConstantBufferView(shader_register, register_space, visibility);

			return *this;
		}

		inline CD3DX12_ROOT_PARAMETER& operator[](const MSTRING& name) {

			return m_root_params[m_mapper.at(name)];
		}



		inline CD3DX12_ROOT_PARAMETER& operator[](const MINT index) {

			return m_root_params[index];
		}



		CD3DX12_ROOT_PARAMETER* Get() {
			return reinterpret_cast<CD3DX12_ROOT_PARAMETER*>(m_root_params.data());
		}


	};
}