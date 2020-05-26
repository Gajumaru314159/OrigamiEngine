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
Output BasicVS(float4 pos : POSITION, float2 uv : TEXCOORD)
{
    Output o;
    o.pos = pos;
    o.uv = uv;
    return o;
}