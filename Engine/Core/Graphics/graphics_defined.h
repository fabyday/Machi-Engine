//
// Created by yabai on 2023/01/18.
//

#ifndef MACHI_ENGINE_GRAPHICS_DEFINED_H
#define MACHI_ENGINE_GRAPHICS_DEFINED_H


namespace Machi {



	enum ShaderType {
		MACHI_VERTEX_SHADER,
		MACHI_PIXEL_SHADER
	};

	enum ShaderInputType {
		MACHI_PER_VERTEX,
		MACHI_PER_INSTANCE,
	};

	enum BufferResourceOption {
		ResourceStorageModeManaged
	};



	enum RenderTargetFormat {
		MACHI_FORAMT_R8G8B8A8_UNORM
	};

	enum SignatureContextElements{
		MACHI_INLINE_CONSTANT,
		MACHI_INLINE_CONSTANT_BUFFER_VIEW_DESCRIPTOR,
		MACHI_INLINE_SHADER_RESOURCE_VIEW_DESCRIPTOR,
		MACHI_INLINE_UNORDERED_ACCESS_VIEW_DESCRIPTOR,
		MACHI_TABLE_CONSTANT_BUFFER_VIEW_DESCRIPTOR,
		MACHI_TABLE_SHADER_RESOURCE_VIEW_DESCRIPTOR,
		MACHI_TABLE_UNORDERED_ACCESS_VIEW_DESCRIPTOR,
		MACHI_TABLE_SAMPLER,
		MACHI_ROOT_TABLE,
	};

	enum ShaderVisibility
	{
		MACHI_SHADER_VISIBILITY_ALL = 0,
		MACHI_SHADER_VISIBILITY_VERTEX = 1,
		MACHI_SHADER_VISIBILITY_HULL = 2,
		MACHI_SHADER_VISIBILITY_DOMAIN = 3,
		MACHI_SHADER_VISIBILITY_GEOMETRY = 4,
		MACHI_SHADER_VISIBILITY_PIXEL = 5,
		MACHI_SHADER_VISIBILITY_AMPLIFICATION = 6,
		MACHI_SHADER_VISIBILITY_MESH = 7
	};
	enum BufferUsage {
		MACHI_CPU_ACCESS_NONE,
		MACHI_CPU_ACCESS_DYNAMIC,
		MACHI_CPU_ACCESS_READ_WRITE,
		MACHI_CPU_ACCESS_SCRATCH,
		MACHI_CPU_ACCESS_FIELD,
		MACHI_USAGE_SHADER_INPUT,
		MACHI_USAGE_RENDER_TARGET_OUTPUT,
		MACHI_USAGE_BACK_BUFFER,
		MACHI_USAGE_SHARED,
		MACHI_USAGE_READ_ONLY,
		MACHI_USAGE_DISCARD_ON_PRESENT,
		MACHI_USAGE_UNORDERED_ACCESS,
	};
	enum SwapEffect {
		MACHI_SWAP_EFFECT_DISCARD = 0,
		MACHI_SWAP_EFFECT_SEQUENTIAL = 1,
		MACHI_SWAP_EFFECT_FLIP_SEQUENTIAL = 3,
		MACHI_SWAP_EFFECT_FLIP_DISCARD = 4
	};

	enum InputDataForamt {
		MACHI_FORMAT_R32G32B32_FLOAT,
		MACHI_FORMAT_R32G32_FLOAT
	};
	enum InputClassType {
		MACHI_CLASSFICATION_PER_VERTEX, MACHI_CLASSFICATION_PER_INSTANCE
	};

	 enum DescriptorHeapType
	{
		MACHI_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,    // Constant buffer/Shader resource/Unordered access views
		MACHI_DESCRIPTOR_HEAP_TYPE_SAMPLER,        // Samplers
		MACHI_DESCRIPTOR_HEAP_TYPE_RTV,            // Render target view
		MACHI_DESCRIPTOR_HEAP_TYPE_DSV,            // Depth stencil view
		MACHI_DESCRIPTOR_HEAP_TYPE_NUM_TYPES       // Simply the number of descriptor heap types
	} ;


	 enum DescriptorHeapFlags
	 {
		 MACHI_DESCRIPTOR_HEAP_FLAG_NONE = 0,
		 MACHI_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE = 0x1
	 } 	;



	 enum TextureType {
		MACHI_TEXTURE_1D,
		MACHI_TEXTURE_2D,
		MACHI_TEXTURE_3D,
	 };

	enum ResourceState {
		MACHI_RESOURCE_STATE_COMMON,
		MACHI_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER = 0x1,
		MACHI_RESOURCE_STATE_INDEX_BUFFER = 0x2,
		MACHI_RESOURCE_STATE_RENDER_TARGET = 0x4,
		MACHI_RESOURCE_STATE_UNORDERED_ACCESS = 0x8,
		MACHI_RESOURCE_STATE_DEPTH_WRITE = 0x10,
		MACHI_RESOURCE_STATE_DEPTH_READ = 0x20,
		MACHI_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE = 0x40,
		MACHI_RESOURCE_STATE_PIXEL_SHADER_RESOURCE = 0x80,
		MACHI_RESOURCE_STATE_STREAM_OUT = 0x100,
		MACHI_RESOURCE_STATE_INDIRECT_ARGUMENT = 0x200,
		MACHI_RESOURCE_STATE_COPY_DEST = 0x400,
		MACHI_RESOURCE_STATE_COPY_SOURCE = 0x800,
		MACHI_RESOURCE_STATE_RESOLVE_DEST = 0x1000,
		MACHI_RESOURCE_STATE_RESOLVE_SOURCE = 0x2000,
		MACHI_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE = 0x400000,
		MACHI_RESOURCE_STATE_SHADING_RATE_SOURCE = 0x1000000,
		MACHI_RESOURCE_STATE_GENERIC_READ = (((((0x1 | 0x2) | 0x40) | 0x80) | 0x200) | 0x800),
		MACHI_RESOURCE_STATE_ALL_SHADER_RESOURCE = (0x40 | 0x80),
		MACHI_RESOURCE_STATE_PRESENT = 0,
		MACHI_RESOURCE_STATE_PREDICATION = 0x200,
		MACHI_RESOURCE_STATE_VIDEO_DECODE_READ = 0x10000,
		MACHI_RESOURCE_STATE_VIDEO_DECODE_WRITE = 0x20000,
		MACHI_RESOURCE_STATE_VIDEO_PROCESS_READ = 0x40000,
		MACHI_RESOURCE_STATE_VIDEO_PROCESS_WRITE = 0x80000,
		MACHI_RESOURCE_STATE_VIDEO_ENCODE_READ = 0x200000,
		MACHI_RESOURCE_STATE_VIDEO_ENCODE_WRITE = 0x800000
	};
	enum ResourceFormat{
		MACHI_FORMAT_UNKNOWN = 0,
		MACHI_FORMAT_R32G32B32A32_TYPELESS = 1,
		MACHI_FORMAT_R32G32B32A32_FLOAT = 2,
		MACHI_FORMAT_R32G32B32A32_UINT = 3,
		MACHI_FORMAT_R32G32B32A32_SINT = 4,
		MACHI_FORMAT_R32G32B32_TYPELESS = 5,
		MACHI_FORMAT_R32G32B32_FLOAT = 6,
		MACHI_FORMAT_R32G32B32_UINT = 7,
		MACHI_FORMAT_R32G32B32_SINT = 8,
		MACHI_FORMAT_R16G16B16A16_TYPELESS = 9,
		MACHI_FORMAT_R16G16B16A16_FLOAT = 10,
		MACHI_FORMAT_R16G16B16A16_UNORM = 11,
		MACHI_FORMAT_R16G16B16A16_UINT = 12,
		MACHI_FORMAT_R16G16B16A16_SNORM = 13,
		MACHI_FORMAT_R16G16B16A16_SINT = 14,
		MACHI_FORMAT_R32G32_TYPELESS = 15,
		MACHI_FORMAT_R32G32_FLOAT = 16,
		MACHI_FORMAT_R32G32_UINT = 17,
		MACHI_FORMAT_R32G32_SINT = 18,
		MACHI_FORMAT_R32G8X24_TYPELESS = 19,
		MACHI_FORMAT_D32_FLOAT_S8X24_UINT = 20,
		MACHI_FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
		MACHI_FORMAT_X32_TYPELESS_G8X24_UINT = 22,
		MACHI_FORMAT_R10G10B10A2_TYPELESS = 23,
		MACHI_FORMAT_R10G10B10A2_UNORM = 24,
		MACHI_FORMAT_R10G10B10A2_UINT = 25,
		MACHI_FORMAT_R11G11B10_FLOAT = 26,
		MACHI_FORMAT_R8G8B8A8_TYPELESS = 27,
		MACHI_FORMAT_R8G8B8A8_UNORM = 28,
		MACHI_FORMAT_R8G8B8A8_UNORM_SRGB = 29,
		MACHI_FORMAT_R8G8B8A8_UINT = 30,
		MACHI_FORMAT_R8G8B8A8_SNORM = 31,
		MACHI_FORMAT_R8G8B8A8_SINT = 32,
		MACHI_FORMAT_R16G16_TYPELESS = 33,
		MACHI_FORMAT_R16G16_FLOAT = 34,
		MACHI_FORMAT_R16G16_UNORM = 35,
		MACHI_FORMAT_R16G16_UINT = 36,
		MACHI_FORMAT_R16G16_SNORM = 37,
		MACHI_FORMAT_R16G16_SINT = 38,
		MACHI_FORMAT_R32_TYPELESS = 39,
		MACHI_FORMAT_D32_FLOAT = 40,
		MACHI_FORMAT_R32_FLOAT = 41,
		MACHI_FORMAT_R32_UINT = 42,
		MACHI_FORMAT_R32_SINT = 43,
		MACHI_FORMAT_R24G8_TYPELESS = 44,
		MACHI_FORMAT_D24_UNORM_S8_UINT = 45,
		MACHI_FORMAT_R24_UNORM_X8_TYPELESS = 46,
		MACHI_FORMAT_X24_TYPELESS_G8_UINT = 47,
		MACHI_FORMAT_R8G8_TYPELESS = 48,
		MACHI_FORMAT_R8G8_UNORM = 49,
		MACHI_FORMAT_R8G8_UINT = 50,
		MACHI_FORMAT_R8G8_SNORM = 51,
		MACHI_FORMAT_R8G8_SINT = 52,
		MACHI_FORMAT_R16_TYPELESS = 53,
		MACHI_FORMAT_R16_FLOAT = 54,
		MACHI_FORMAT_D16_UNORM = 55,
		MACHI_FORMAT_R16_UNORM = 56,
		MACHI_FORMAT_R16_UINT = 57,
		MACHI_FORMAT_R16_SNORM = 58,
		MACHI_FORMAT_R16_SINT = 59,
		MACHI_FORMAT_R8_TYPELESS = 60,
		MACHI_FORMAT_R8_UNORM = 61,
		MACHI_FORMAT_R8_UINT = 62,
		MACHI_FORMAT_R8_SNORM = 63,
		MACHI_FORMAT_R8_SINT = 64,
		MACHI_FORMAT_A8_UNORM = 65,
		MACHI_FORMAT_R1_UNORM = 66,
		MACHI_FORMAT_R9G9B9E5_SHAREDEXP = 67,
		MACHI_FORMAT_R8G8_B8G8_UNORM = 68,
		MACHI_FORMAT_G8R8_G8B8_UNORM = 69,
		MACHI_FORMAT_BC1_TYPELESS = 70,
		MACHI_FORMAT_BC1_UNORM = 71,
		MACHI_FORMAT_BC1_UNORM_SRGB = 72,
		MACHI_FORMAT_BC2_TYPELESS = 73,
		MACHI_FORMAT_BC2_UNORM = 74,
		MACHI_FORMAT_BC2_UNORM_SRGB = 75,
		MACHI_FORMAT_BC3_TYPELESS = 76,
		MACHI_FORMAT_BC3_UNORM = 77,
		MACHI_FORMAT_BC3_UNORM_SRGB = 78,
		MACHI_FORMAT_BC4_TYPELESS = 79,
		MACHI_FORMAT_BC4_UNORM = 80,
		MACHI_FORMAT_BC4_SNORM = 81,
		MACHI_FORMAT_BC5_TYPELESS = 82,
		MACHI_FORMAT_BC5_UNORM = 83,
		MACHI_FORMAT_BC5_SNORM = 84,
		MACHI_FORMAT_B5G6R5_UNORM = 85,
		MACHI_FORMAT_B5G5R5A1_UNORM = 86,
		MACHI_FORMAT_B8G8R8A8_UNORM = 87,
		MACHI_FORMAT_B8G8R8X8_UNORM = 88,
		MACHI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
		MACHI_FORMAT_B8G8R8A8_TYPELESS = 90,
		MACHI_FORMAT_B8G8R8A8_UNORM_SRGB = 91,
		MACHI_FORMAT_B8G8R8X8_TYPELESS = 92,
		MACHI_FORMAT_B8G8R8X8_UNORM_SRGB = 93,
		MACHI_FORMAT_BC6H_TYPELESS = 94,
		MACHI_FORMAT_BC6H_UF16 = 95,
		MACHI_FORMAT_BC6H_SF16 = 96,
		MACHI_FORMAT_BC7_TYPELESS = 97,
		MACHI_FORMAT_BC7_UNORM = 98,
		MACHI_FORMAT_BC7_UNORM_SRGB = 99,
		MACHI_FORMAT_AYUV = 100,
		MACHI_FORMAT_Y410 = 101,
		MACHI_FORMAT_Y416 = 102,
		MACHI_FORMAT_NV12 = 103,
		MACHI_FORMAT_P010 = 104,
		MACHI_FORMAT_P016 = 105,
		MACHI_FORMAT_420_OPAQUE = 106,
		MACHI_FORMAT_YUY2 = 107,
		MACHI_FORMAT_Y210 = 108,
		MACHI_FORMAT_Y216 = 109,
		MACHI_FORMAT_NV11 = 110,
		MACHI_FORMAT_AI44 = 111,
		MACHI_FORMAT_IA44 = 112,
		MACHI_FORMAT_P8 = 113,
		MACHI_FORMAT_A8P8 = 114,
		MACHI_FORMAT_B4G4R4A4_UNORM = 115,

		MACHI_FORMAT_P208 = 130,
		MACHI_FORMAT_V208 = 131,
		MACHI_FORMAT_V408 = 132,


		MACHI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE = 189,
		MACHI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE = 190,


		MACHI_FORMAT_FORCE_UINT = 0xffffffff
	};
	enum PrimitiveType {
		MACHI_PRIMITIVE_TOPOLOGY_UNDEFINED = 0,
		MACHI_PRIMITIVE_TOPOLOGY_POINTLIST = 1,
		MACHI_PRIMITIVE_TOPOLOGY_LINELIST = 2,
		MACHI_PRIMITIVE_TOPOLOGY_LINESTRIP = 3,
		MACHI_PRIMITIVE_TOPOLOGY_TRIANGLELIST = 4,
		MACHI_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = 5,
		MACHI_PRIMITIVE_TOPOLOGY_LINELIST_ADJ = 10,
		MACHI_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ = 11,
		MACHI_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ = 12,
		MACHI_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ = 13,
		/*D3D_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST = 33,
		D3D_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST = 34,
		D3D_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST = 35,
		D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST = 36,
		D3D_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST = 37,
		D3D_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST = 38,
		D3D_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST = 39,
		D3D_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST = 40,
		D3D_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST = 41,
		D3D_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST = 42,
		D3D_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST = 43,
		D3D_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST = 44,
		D3D_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST = 45,
		D3D_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST = 46,
		D3D_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST = 47,
		D3D_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST = 48,
		D3D_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST = 49,
		D3D_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST = 50,
		D3D_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST = 51,
		D3D_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST = 52,
		D3D_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST = 53,
		D3D_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST = 54,
		D3D_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST = 55,
		D3D_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST = 56,
		D3D_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST = 57,
		D3D_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST = 58,
		D3D_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST = 59,
		D3D_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST = 60,
		D3D_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST = 61,
		D3D_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST = 62,
		D3D_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST = 63,
		D3D_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST = 64,
		D3D10_PRIMITIVE_TOPOLOGY_UNDEFINED = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED,
		D3D10_PRIMITIVE_TOPOLOGY_POINTLIST = D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
		D3D10_PRIMITIVE_TOPOLOGY_LINELIST = D3D_PRIMITIVE_TOPOLOGY_LINELIST,
		D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
		D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
		D3D10_PRIMITIVE_TOPOLOGY_LINELIST_ADJ = D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
		D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
		D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
		D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ,
		D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED,
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST = D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST = D3D_PRIMITIVE_TOPOLOGY_LINELIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ = D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
		D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ,
		D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST,
		D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST*/
	};









}








#endif //MACHI_ENGINE_GRAPHICS_DEFINED_H
