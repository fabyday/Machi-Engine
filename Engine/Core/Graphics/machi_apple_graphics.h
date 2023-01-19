//
// Created by yabai on 2023/01/18.
//

#ifndef MACHI_ENGINE_MACHI_APPLE_GRAPHICS_H
#define MACHI_ENGINE_MACHI_APPLE_GRAPHICS_H
#include "Platform/Apple/config.h"
#include <simd/simd.h>
#include <MachiMetal/metal.h>
#include <Platform/types.h>
#include <map>
#include <utility>
#include <vector>
#include "graphics_defined.h"
static constexpr size_t kMaxFramesInFlight = 3;
namespace Machi {
	class MachiAppDelegate;
	class NativeGraphicsManager;
	class Buffer {
		friend NativeGraphicsManager;
		Buffer() {

		}

	};

	class Shader {
		friend NativeGraphicsManager;




		//        MTL::Library* m_shader_lib;
		MTL::Function* m_function_entry;
	public:
		typedef struct ShaderInfo {

			ShaderInputType m_input_type;
			MSTRING m_func_name;

		}ShaderInfo;
		struct ShaderDesc {
			std::map<MSTRING, std::vector<ShaderInfo>> m_resource;

			struct ShaderDesc& add_resource(MSTRING filename, MSTRING func_name, ShaderInputType input_type) {
				m_resource[filename].push_back({ input_type, func_name });
				return *this;
			}

			struct ShaderInfo& operator+() {

			}
		};

	private:

		ShaderInfo* m_shaderinfo;
		Shader(ShaderInfo* info, MTL::Function* func) :m_function_entry(func), m_shaderinfo(info) {};
	public:
		MSTRING get_name() { return m_shaderinfo->m_func_name; };
		ShaderInputType get_input_type() { return m_shaderinfo->m_input_type; };
		MTL::Function* get_shader_resource() { return m_function_entry; };
	};

	class Pipeline {
		MTL::RenderPipelineState* m_pipeline;

		friend NativeGraphicsManager;
		Pipeline(MTL::RenderPipelineState* pipeline) : m_pipeline(pipeline) {


		}



		~Pipeline() {
			if (m_pipeline != nullptr) {
				m_pipeline->release();
			}
		}
	};

	class CommandQueue {
		MTL::CommandQueue* m_command_queue;

		friend class NativeGraphicsManager;
		CommandQueue(MTL::Device* device) :m_command_queue(device->newCommandQueue()) {

		}

		~CommandQueue() {
			if (m_command_queue != nullptr) {
				m_command_queue->release();
			}
		}

	};
	//this class manage native Grpahcis resource.
	class NativeGraphicsManager final {
		static NativeGraphicsManager* m_instance;

		MTL::Device* m_device;
		NativeGraphicsManager(MTL::Device* device) :m_device(device) {};

		friend class MachiAppDelegate;//this initialize this class.
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



	class Renderer {
	public:
		Renderer(MTL::Device* pDevice);

		~Renderer();

		void buildShaders();

		void buildBuffers();

		void draw(MTK::View* pView);

	private:
		MTL::Device* _pDevice;
		MTL::CommandQueue* _pCommandQueue;
		MTL::Library* _pShaderLibrary;
		MTL::RenderPipelineState* _pPSO;
		MTL::Buffer* _pVertexDataBuffer;
		MTL::Buffer* _pInstanceDataBuffer[kMaxFramesInFlight];
		MTL::Buffer* _pIndexBuffer;
		float _angle;
		int _frame;
		dispatch_semaphore_t _semaphore;
		static const int kMaxFramesInFlight;
	};
}

#endif //MACHI_ENGINE_MACHI_APPLE_GRAPHICS_H
