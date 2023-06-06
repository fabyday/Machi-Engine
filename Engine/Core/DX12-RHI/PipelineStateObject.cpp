#include "PipelineStateObject.h"
//using namespace Machi;
using namespace Machi::NativeGraphics;
#include "dxhelper.h"

PipeLineState& PipeLineState::add_shader(Shader& shader)
{

	// TODO: insert return statement here
	switch (shader.m_type) {
	case MACHI_VERTEX_SHADER:
		m_desc.VS = shader.Get();
		break;
	case MACHI_PIXEL_SHADER:
		m_desc.PS = shader.Get();
		break;

	}
	return *this;
}

PipeLineState& PipeLineState::set_rootsignature(RootSignature& rootsignature)
{
	m_desc.pRootSignature = rootsignature.Get();
	return *this;
}

PipeLineState& PipeLineState::set_depth_stencil_state(bool depth, bool stencil)
{
	m_desc.DepthStencilState.DepthEnable = depth;
	m_desc.DepthStencilState.StencilEnable = stencil;

	return *this;
}

PipeLineState& PipeLineState::set_samplemask(MUINT sample_mask)
{
	m_desc.SampleMask = sample_mask;

	return *this;
}

PipeLineState& PipeLineState::set_primitive_topology_type(PrimitiveType type)
{
	//D3D12
	switch (type) {
	case MACHI_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED:
		m_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
		break;
	case MACHI_PRIMITIVE_TOPOLOGY_TYPE_POINT:
		m_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
		break;
	case MACHI_PRIMITIVE_TOPOLOGY_TYPE_LINE:
		m_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
		break;
	case MACHI_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE:
		m_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		break;
	case MACHI_PRIMITIVE_TOPOLOGY_TYPE_PATCH:
		m_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH;
		break;
	}

	return *this;
}

PipeLineState& PipeLineState::set_num_render_target(MUINT size)
{
	m_desc.NumRenderTargets = size;
	return *this;
}

PipeLineState& PipeLineState::set_render_target_format(RenderTargetFormat format)
{
	m_desc.RTVFormats[0] = resource_format_convert(format);
	return *this;
}

PipeLineState& PipeLineState::set_sample_count(SampleType type)
{
	switch (type) {
	case SampleType::MSAAx4:
		m_desc.SampleDesc.Count = 4;
		break;
	case SampleType::MSAAx8:
		m_desc.SampleDesc.Count = 8;
		break;
	default:
		m_desc.SampleDesc.Count = 1;
	}
	return *this;
}


PipeLineState& PipeLineState::add_input_schema(MSTRING& name, ShaderInputFormat format_type, ShaderInputType input_classfication_type, MUINT semantic_index, MUINT inputslot, MUINT alignment_by_offset, MUINT instance_data_step_rate)
{
	std::string asci_name(name.begin(), name.end());
	//asci_name.assign(name.begin(), name.end());
	D3D12_INPUT_ELEMENT_DESC t = { asci_name.c_str(), semantic_index, resource_format_convert(format_type), inputslot, alignment_by_offset, shader_input_type_convert(input_classfication_type), instance_data_step_rate };
	m_input_desc.push_back(t);
	//m_input_desc.emplace_back();
	return *this;
}

bool PipeLineState::build(Device& device)
{



	// Describe and create the graphics pipeline state object (PSO).
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pso_desc = {};
	m_desc.InputLayout = { m_input_desc.data(), static_cast<MUINT>(m_input_desc.size())};
	m_desc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	m_desc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);

	ThrowIfFailed(device->CreateGraphicsPipelineState(&m_desc, IID_PPV_ARGS(&m_pipeline_object)));
	return true;
}
