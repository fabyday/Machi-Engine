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

}








#endif //MACHI_ENGINE_GRAPHICS_DEFINED_H
