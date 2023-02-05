//MIT License 
//Copyright(c) 2022 fabyday
// 
// 
//Permission is hereby granted, free of charge, to any person
//obtaining a copy of this softwareand associated documentation
//files(the "Software"), to deal in the Software without
//restriction, including without limitation the rights to use,
//copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the
//Software is furnished to do so, subject to the following
//conditions :
//
//The above copyright noticeand this permission notice shall be
//included in all copies or substantial portions of the Software.
// 
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//OTHER DEALINGS IN THE SOFTWARE.
#pragma once

#include <d3dx12.h>




using namespace Microsoft;
#include <Graphics/GraphicManager.h>
#include "config.h"
#include "d3d12.h"
#include "d3dx12.h"
#include "os_native.h"
#include "dxhelper.h"
#include <wrl.h> // ComPtr header
#include <shellapi.h>

#include <directxmath.h>
#include <D3Dcompiler.h>
#include <dxgi1_4.h>


#include <d3d12sdklayers.h> // for debugging
#include <set>
#include <map>
#include <DirectXMath.h>
#include <spdlog/spdlog.h>
#include <utility>



template <typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;
using namespace DirectX;


namespace Machi {
	class ApplicationManager;
	class GraphicsManager;


	class Device;
	class CommandQueue;
	class SwapChain;



	//this class manage native Grpahcis resource.
	class NativeGraphicsManager final {
		static NativeGraphicsManager* m_instance;
		ComPtr<IDXGIFactory4> m_factory = nullptr;
		std::unique_ptr<Device> m_device_ref = nullptr;
		static std::unique_ptr<GraphicsContextManager> instance;

		friend class ApplicationManager;
		friend class GraphicsManager;
		Viewport m_viewport;
		NativeGraphicsManager() : {};

	public:
		static NativeGraphicsManager* get_instance() {
			return m_instance;
		}


		// Buffer* make_buffer();
		// make_pipeline();
		// make_shader();

		Shader* make_shader(Shader::ShaderDesc& shaderDesc);
		Pipeline* make_pipeline(std::vector<Shader>& shaders);
		Buffer* make_buffer(MLENGTH buf_size, enum BufferResourceOption option);

		// render();

		~NativeGraphicsManager() {

			if (m_device != nullptr) {
				m_device->release();
			}
		}

	};

	class RootSignature final {
		ComPtr<ID3D12RootSignature> m_rootsignature;
		void init_rootsignature(Device& device);
		friend NativeGraphicsManager;
	public:

	};
	class Device final {

		ComPtr<ID3D12Device> m_device;
		friend class GraphicsContextManager;
		bool init_device(ComPtr<IDXGIFactory4> factory);
	public:
		ComPtr<ID3D12Device> get_device() { return m_device; };
	};

	class CommandQueue final {
		ComPtr<ID3D12CommandQueue> m_command_queue;
		SwapChain m_swapchain;
		bool init_queue(ComPtr<ID3D12Device> device);
		bool connect_swapchian(SwapChain sc);




		bool execute_command(); 1

	};

	class Viewport final {
		D3D12_VIEWPORT m_viewport;
		D3D12_RECT m_scissor_rect;
		bool init_viewport(MINT width, MINT height);
	};
	class Shader;

	class Pipeline {

	
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

		void init_pipeline();

		Pipeline& add_input_schema(MSTRING& name,
			input_data_format format_type,
			input_class_type input_classfication_type,
			MUINT index = 0);


		bool Pipeline& build();


	};



	class Buffer  {
		enum Type { COSNTANT, TEXTURE, };

		ComPtr<ID3D12Resource> m_vertexBuffer;
		std::unique_ptr<IBufferData> m_data;
		MUINT size;

		Buffer& create(Device& device);//call last
		get_buffer_view();


		MUINT get_vertex_size();
		MUINT get_vertex_stride();

	};

	class DescriptorHeap {
		ComPtr<ID3D12DescriptorHeap> m_rtvHeap;

	};

	class SwapChain final {
		ComPtr<IDXGISwapChain3> m_swaphain;
		void init_swapchain(ComPtr<IDXGIFactory4> factory, MUINT frame_count_, MUINT width, MUINT height);
		bool add_resources();

	};

	class ICommandAllocator {



	private:
		virtual ICommandAllocator& create(Device& device) = 0;


	};


	class CommandAllocator: public ICommandAllocator {
		ComPtr<ID3D12CommandAllocator> m_command_allocator;

		ComPtr<ID3D12CommandAllocator> m_bundleAllocator;
		virtual ICommandAllocator& create(Device& device) override;

	};
	class BundleAllocator : public ICommandAllocator {
		ComPtr<ID3D12CommandAllocator> m_bundle_allocator;

		ComPtr<ID3D12CommandAllocator> m_bundleAllocator;
		virtual ICommandAllocator& create(Device& device) override;

	};

	class IRenderCommand {

	public:

	protected:
		virtual IRenderCommand& create(Device& device, ICommandAllocator& alloc) = 0;
		virtual bool execute() = 0;
		
		virtual IRenderCommand& reset() = 0;

		virtual IRenderCommand& set_root_signature(Device& device, Pipeline& pipline) = 0;
		virtual IRenderCommand& set_primitive_topology(Device& device, Pipeline& pipline) = 0;
		virtual IRenderCommand& set_vertex_buffer(Device& device, Pipeline& pipline) = 0;
		virtual IRenderCommand& set_viewport(Viewport& viewport) = 0;
		virtual IRenderCommand& set_viewport(Viewport& viewport) = 0;
		virtual IRenderCommand& set_render_targets(DescriptorHeap& rtv_heap, MUINT frame_idx) = 0;
		virtual IRenderCommand& clear_render_target_view(MFLOAT r, MFLOAT g, MFLOAT b, MFLOAT a) = 0;
		virtual IRenderCommand& clear_render_target_view(MFLOAT r, MFLOAT g, MFLOAT b, MFLOAT a) = 0;
		virtual IRenderCommand& resource_barrier_transistion(const ResourceState& before, const ResourceState before& after) = 0;


		virtual IRenderCommand& close() = 0;


		//virtual IRenderCommand& set_render_targets(DescriptorHeap& viewport) = 0;

		

		friend class CommandQueue;
		virtual ID3D12GraphicsCommandList* get() = 0;

	};


	class Bundle :public IRenderCommand {
	private:
		ComPtr<ID3D12CommandAllocator> m_bundle_allocator;
		ComPtr<ID3D12GraphicsCommandList> m_bundle;

	public:

	protected:
		ID3D12GraphicsCommandList* get() override;

	};

	class CommandList public IRenderCommand {
		ComPtr<ID3D12GraphicsCommandList> m_command_list;
		ComPtr<ID3D12CommandAllocator> m_command_allocator;
		IRenderCommand::description m_desc;


	protected:
		virtual IRenderCommand& set_root_signature(Device& device, Pipeline& pipline);
		virtual IRenderCommand& set_primitive_topology(Device& device, Pipeline& pipline);
		virtual IRenderCommand& set_vertex_buffer(Device& device, Pipeline& pipline);
		virtual IRenderCommand& reset() = 0;

		friend class CommandQueue;
		virtual ID3D12GraphicsCommandList* get() override;
		
		



		
	};




	class Shader final {
		enum shader_type { VERTEX, PIXEL };
		enum shader_status { PRECOMPILED };
		bool m_precompiled_flag;
		MSTRING m_name;

		ComPtr<ID3DBlob> m_shader;

		Shader& add_resource(MSTRING& filename, shader_type type);
		Shader& input_description(MSTRING& input_name);
		Shader& init_shader();
	};


}