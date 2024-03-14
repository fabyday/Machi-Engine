#include "NativeGraphicsManager.h"

using namespace Machi::NativeGraphics;

NativeGraphicsManager* NativeGraphicsManager::instance_ = nullptr;


bool NativeGraphicsManager::initialize()
{
	
	m_device = std::make_shared<Device>();
	if (!m_device->init_device()) {
		return false;
	}

	m_command_queue = std::make_shared<CommandQueue>();
	if (!m_command_queue->init(m_device)) {
		return false;
	}
	m_swapchain = std::make_shared<SwapChain>();
	if (!m_swapchain->init(m_command_queue)) {
		return false;
	}
	m_sync_manager = std::make_shared<GraphicsSyncManager>();
	if (!m_sync_manager->create(m_device, m_swapchain->get_frame_num())) {
		return false;
	}
	initialize_default_root_signature();
	initialize_default_PSO();
	return true;
}

bool Machi::NativeGraphics::NativeGraphicsManager::initialize_default_PSO()
{
	auto p_pso = std::make_shared<PipeLineState>();
	p_pso->set_rootsignature(this->m_rootsignatures[0]);
	std::shared_ptr<Shader> pixel_shader = std::make_shared<Shader>();
	std::shared_ptr<Shader> vertex_shader = std::make_shared<Shader>();
	
	pixel_shader->set_shader_type(Machi::Graphics::ShaderType::MACHI_PIXEL_SHADER);
	MSTRING pixel = SHADER_RESOURCE_DIRECTORY"/test_pixel_shader.hlsl";
	pixel_shader->set_function_from_file(pixel, MTEXT("PSMain"));
	vertex_shader->set_shader_type(Machi::Graphics::ShaderType::MACHI_VERTEX_SHADER);

	MSTRING txt = SHADER_RESOURCE_DIRECTORY"/test_vertex_shader.hlsl";
	vertex_shader->set_function_from_file(txt, MTEXT("VSMain"));
	vertex_shader->create();
	pixel_shader->create();
	p_pso->add_shader(vertex_shader);
	p_pso->add_shader(pixel_shader);
	p_pso->set_primitive_topology_type(Machi::Graphics::MACHI_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);
	p_pso->set_render_target_format(Machi::Graphics::MACHI_FORMAT_R8G8B8A8_UNORM); //TODO
	p_pso->set_depth_stencil_state(true, true);
	p_pso->set_num_render_target(m_swapchain->get_frame_num());
	
	p_pso->set_samplemask(UINT_MAX);

	p_pso->add_input_schema(MTEXT("POSITION"), MACHI_FORMAT_R32G32B32_FLOAT, MACHI_PER_VERTEX, 0, 0, 0, 0);
	p_pso->add_input_schema(MTEXT("COLOR"), MACHI_FORMAT_R32G32B32A32_FLOAT, MACHI_PER_VERTEX, 0, 0, 12, 0);
	// Define the vertex input layout.
	p_pso->build(m_device);




	m_pipelines.emplace_back(p_pso);

	return true;
}
bool Machi::NativeGraphics::NativeGraphicsManager::initialize_default_command_list()
{
	for (int i = 0; i < m_swapchain->get_frame_num(); i++) {
		m_command_list.emplace_back(std::make_shared< Machi::NativeGraphics::CommandList>());
		m_command_list[i]->initialize(m_device, m_command_allocator, m_pipelines[0]);
	}

		


	return true;
}

bool Machi::NativeGraphics::NativeGraphicsManager::initialize_default_root_signature()
{
	auto p_signature = std::make_shared < RootSignature>();
	RootParameter root_param;
	//root_param.add_inline_cbv(16, 0); // world mat
	//root_param.add_inline_cbv(16, 1); // camera mat
	//root_param.add_inline_cbv(16, 2); // proj mat
	p_signature->init(this->m_device, root_param);
	
	m_rootsignatures.emplace_back(p_signature);
	return true;
}

bool Machi::NativeGraphics::NativeGraphicsManager::render(std::shared_ptr<Machi::Graphics::Renderer> object)
{



	if (object == nullptr)
		return false;
	std::shared_ptr<Machi::Geometry::Mesh> mesh =  object->get_mesh();
	
	
	
	return true;
}



std::shared_ptr<Machi::NativeGraphics::Buffer> NativeGraphicsManager::alloc_buffer(MUINT byte_size) {
	
	
	Machi::NativeGraphics::Buffer* buffer = new Machi::NativeGraphics::Buffer();
	//m_buffer_list.emplace_back(std::make_shared<>());
	//std::shared_ptr<Machi::NativeGraphics::Buffer> buffer = *m_buffer_list.rbegin();
	buffer->set_size(byte_size);
	buffer->init(m_device);
	//return buffer;
	return std::make_shared<Buffer>();
}
