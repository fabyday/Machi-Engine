#pragma once

#include "Commons.h"
#include "RootSignature.h"
#include "Shader.h"
#include "Device.h"
#include <map>
#include "native_format_converter.h"

namespace Machi {
	namespace NativeGraphics {
		class PipeLineState {

			ComPtr<ID3D12PipelineState> m_pipeline_object;
			D3D12_GRAPHICS_PIPELINE_STATE_DESC m_desc;

			std::map<MSTRING, Shader> m_shader;
			std::vector<D3D12_INPUT_ELEMENT_DESC> m_input_desc;
			MUINT m_input_offset;
		public:
			//PipeLineState& add_vertex_shader(const MSTRING& filename);
			//PipeLineState& add_vertex_shader(Shader& shder);
			//PipeLineState& add_pixel_shader(const MSTRING& filename);
			//PipeLineState& add_pixel_shader(Shader& shader);
			PipeLineState& add_shader(std::shared_ptr<Shader> shader);
			//PipeLineState& add_shader(MSTRING& filename);


			PipeLineState& set_rootsignature(std::shared_ptr<RootSignature> rootsignature);
			PipeLineState& set_depth_stencil_state(bool depth, bool stencil);
			PipeLineState& set_samplemask(MUINT sample_mask = UINT_MAX);
			PipeLineState& set_primitive_topology_type(PrimitiveType type);
			PipeLineState& set_num_render_target(MUINT target);
			PipeLineState& set_render_target_format(RenderTargetFormat format);
			PipeLineState& set_sample_count(SampleType count);


			PipeLineState& add_input_schema(MSTRING& name, ShaderInputFormat format_type, ShaderInputType input_classfication_type,
				MUINT semantic_index, MUINT inputslot, MUINT alignment_by_offset, MUINT instance_data_step_rate);


			bool build(Device& device);
		};
	}
}