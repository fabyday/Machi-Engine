//
// Created by yabai on 2023/01/18.
//

#ifndef MACHI_ENGINE_GRAPHICS_DEFINED_H
#define MACHI_ENGINE_GRAPHICS_DEFINED_H


namespace Machi{



    enum ShaderType{
        MACHI_VERTEX_SHADER,
        MACHI_PIXEL_SHADER
    };

    enum ShaderInputType{
        MACHI_PER_VERTEX,
        MACHI_PER_INSTANCE,
    };

    enum BufferResourceOption{
        ResourceStorageModeManaged
    };



    enum RenderTargetFormat {
        MACHI_FORAMT_R8G8B8A8_UNORM
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
    enum SwapEffect{
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

 
    enum ResourceState {
        MACHI_RESOURCE_STATE_COMMON ,
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
