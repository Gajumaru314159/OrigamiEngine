Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);
cbuffer Data0 : register(b0)
{
    matrix mat;
};
cbuffer Data1 : register(b1)
{
    float4 col;
};
struct Output
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};
float4 BasicPS(Output i) : SV_TARGET
{
    return float4(tex.Sample(smp, i.uv));
}