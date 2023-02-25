namespace {
	class PipeLineState{

		ComPtr<ID3D12PipelineState> m_pipeline_object;


		std::map<MSTRING, Shader> m_shader;
		std::vector<D3D12_INPUT_ELEMENT_DESC> m_input_desc;
		MUINT m_input_offset;

		Pipeline& add_vertex_shader(const MSTRING& filename);
		Pipeline& add_vertex_shader(Shader& shder);
		Pipeline& add_pixel_shader(const MSTRING& filename);
		Pipeline& add_pixel_shader(Shader& shader);
		Pipeline& add_shader(Shader& shader);

		Pipeline& set_rootsignature(RootSignature& rootsignature);
		Pipeline& set_depth_stencil_state(bool depth, bool stencil);
		Pipeline& set_samplemask(bool depth, bool stencil);
		Pipeline& set_primitive_topology_type(Machi::PrimitiveType type);
		Pipeline& set_num_render_target(MUINT target);
		Pipeline& set_render_target_format(Machi::RenderTargetFormat format);
		Pipeline& set_sample_count(MUINT count);

		void init();

		Pipeline& add_input_schema(MSTRING& name,
			input_data_format format_type,
			input_class_type input_classfication_type,
			MUINT index = 0);


		bool Pipeline& build();
	};
}