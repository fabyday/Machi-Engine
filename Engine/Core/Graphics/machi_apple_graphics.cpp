//
// Created by yabai on 2023/01/19.
//
#include "machi_apple_graphics.h"


Machi::Pipeline *Machi::NativeGraphicsManager::make_pipeline(std::vector<Shader> &shaders) {


    MTL::RenderPipelineDescriptor* p_desc = MTL::RenderPipelineDescriptor::alloc()->init();
    NS::Error* pError = nullptr;

    for(Shader& shader :shaders){
        switch (shader.get_input_type()) {

            case ShaderType::MACHI_VERTEX_SHADER:
                p_desc->setVertexFunction(shader.get_shader_resource());

                break;
            case ShaderType::MACHI_PIXEL_SHADER:

                p_desc->setFragmentFunction(shader.get_shader_resource());
                break;
        }
    }

    p_desc->colorAttachments()->object(0)->setPixelFormat( MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB );

    MTL::RenderPipelineState* p_pso = m_device->newRenderPipelineState( p_desc, &pError );
    if ( !p_pso )
    {
        __builtin_printf( "%s", pError->localizedDescription()->utf8String() );
        assert( false );
    }

    p_desc->release();

    return new Machi::Pipeline(p_pso);


}



Machi::CommandQueue* Machi::NativeGraphicsManager::make_command_queue() {};
Machi::Buffer* Machi::NativeGraphicsManager::make_buffer(MLENGTH buf_size, enum BufferResourceOption option)  {
    MTL:Buffer* re_buf = nullptr;
    switch (option) {
        case BufferResourceOption::ResourceStorageModeManaged:
            re_buf = m_device->newBuffer( buf_size,MTL::ResourceStorageModeManaged);
            break;
    }
    return new Machi::Buffer(re_buf);

};
Machi::Shader* Machi::NativeGraphicsManager::make_shader(Shader::ShaderDesc &shaderDesc) {

    return nullptr;

} ;

Machi::Shader* Machi::NativeGraphicsManager::make_shader(const MSTRING& filename, const MSTRING& function_name, const Shader::ShaderInfo& shaderInfo) {
    using NS::StringEncoding::UTF8StringEncoding;



    NS::Error* pError = nullptr;

    MTL::Library* p_lib = m_device->newLibrary( NS::String::string(filename.c_str(), UTF8StringEncoding), nullptr, &pError );

    if ( !p_lib )
    {
        __builtin_printf( "%s", pError->localizedDescription()->utf8String() );
        assert( false );
    }
    MTL::Function* func = p_lib->newFunction( NS::String::string(function_name.c_str(), UTF8StringEncoding) );

    Shader::ShaderInfo* info = new Shader::ShaderInfo();
    return new Shader(info, func);
}




bool Machi::NativeGraphicsManager::render(Machi::CommandQueue* command_queue, Machi::Pipeline* pipeline){

    using simd::float4;
    using simd::float4x4;

    NS::AutoreleasePool* pPool = NS::AutoreleasePool::alloc()->init();

    _frame = (_frame + 1) % Renderer::kMaxFramesInFlight;
    MTL::Buffer* pInstanceDataBuffer = _pInstanceDataBuffer[ _frame ];

    MTL::CommandBuffer* pCmd = command_queue->commandBuffer();
    dispatch_semaphore_wait( _semaphore, DISPATCH_TIME_FOREVER );
    Renderer* pRenderer = this;
    pCmd->addCompletedHandler( ^void( MTL::CommandBuffer* pCmd ){
        dispatch_semaphore_signal( pRenderer->_semaphore );
    });

    _angle += 0.01f;

    const float scl = 0.1f;
    shader_types::InstanceData* pInstanceData = reinterpret_cast< shader_types::InstanceData *>( pInstanceDataBuffer->contents() );
    for ( size_t i = 0; i < kNumInstances; ++i )
    {
        float iDivNumInstances = i / (float)kNumInstances;
        float xoff = (iDivNumInstances * 2.0f - 1.0f) + (1.f/kNumInstances);
        float yoff = sin( ( iDivNumInstances + _angle ) * 2.0f * M_PI);
        pInstanceData[ i ].instanceTransform = (float4x4){ (float4){ scl * sinf(_angle), scl * cosf(_angle), 0.f, 0.f },
                                                           (float4){ scl * cosf(_angle), scl * -sinf(_angle), 0.f, 0.f },
                                                           (float4){ 0.f, 0.f, scl, 0.f },
                                                           (float4){ xoff, yoff, 0.f, 1.f } };

        float r = iDivNumInstances;
        float g = 1.0f - r;
        float b = sinf( M_PI * 2.0f * iDivNumInstances );
        pInstanceData[ i ].instanceColor = (float4){ r, g, b, 1.0f };
    }
    pInstanceDataBuffer->didModifyRange( NS::Range::Make( 0, pInstanceDataBuffer->length() ) );


    MTL::RenderPassDescriptor* pRpd = pView->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* pEnc = pCmd->renderCommandEncoder( pRpd );

    pEnc->setRenderPipelineState( _pPSO );
    pEnc->setVertexBuffer( _pVertexDataBuffer, /* offset */ 0, /* index */ 0 );
    pEnc->setVertexBuffer( pInstanceDataBuffer, /* offset */ 0, /* index */ 1 );

    //
    // void drawIndexedPrimitives( PrimitiveType primitiveType, NS::UInteger indexCount, IndexType indexType,
    //                             const class Buffer* pIndexBuffer, NS::UInteger indexBufferOffset, NS::UInteger instanceCount );
    pEnc->drawIndexedPrimitives( MTL::PrimitiveType::PrimitiveTypeTriangle,
                                 6, MTL::IndexType::IndexTypeUInt16,
                                 _pIndexBuffer,
                                 0,
                                 kNumInstances );

    pEnc->endEncoding();
    pCmd->presentDrawable( pView->currentDrawable() );
    pCmd->commit();

    pPool->release();

    return true;
}