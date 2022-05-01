//struct PSInput
//{
//    float4 position : SV_POSITION;
//    float4 color : COLOR;
//};
struct PSInput
{
    float4 position : SV_POSITION;
    float4 uv : TEXCOORD;
};
Texture2D g_texture : register(t0);
SamplerState g_sampler :register(s0);

//
//PSInput VSMain(float4 position : POSITION, float4 color : COLOR)
//{
//    PSInput result;
//
//    result.position = position;
//    result.color = color;
//
//    return result;
//}

PSInput VSMain(float4 position : POSITION, float4 uv : TEXCOORD)
{
    PSInput result;

    result.position = position;
    result.uv = uv;

    return result;
}