
cbuffer colorBuffer
{
    float3 color;
};

float4 main(float3 Color : COLOR) : SV_Target
{
    return float4(Color, 1.0f);
}