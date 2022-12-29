//MIT License 
//Copyright(c) 2022 Ji Hyun Roh
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

#include "config.h"



#include "metal-cpp/Foundation/Foundation.hpp"
#include "metal-cpp/Metal/Metal.hpp"
#include "metal-cpp/QuartzCore/QuartzCore.hpp"


struct Vertex
{
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT4 color;
};

struct Triangle {


    int order;

};
struct Buffer{
    MTL::Buffer* buffer_;
};


struct BufferView{

};

class MACHI_API MGraphics {
public:
    virtual void initialize() ;
    virtual void update() ;
    virtual void render() ;
    virtual void destroy() ;


private:

    static const INT frame_count_ = 2;

    // Pipeline objects.
    MTL::Device* device_;
    MTL::CommandQueue* command_queue_;
    MTL::DepthStencilState* depth_stencil_state_;
    MTL::RendererPipelineState* renderer_pipeline_state_;
    MTL::Buffer* vertex_buffer_;
    // App resources.
    ComPtr<ID3D12Resource> m_vertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

    // Synchronization objects.
    UINT m_frameIndex;
    HANDLE m_fenceEvent;
    ComPtr<ID3D12Fence> m_fence;
    UINT64 m_fenceValue;

    int LoadPipeline() ;
    int LoadAssets() ;
    int PopulateCommandList() ;
    int WaitForPreviousFrame() ;


};
