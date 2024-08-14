#include "TransformBufferVar.hlsl"

struct VertexIn
{
	float3 Pos : Position;
	float3 Color : COLOR;
};

struct VertexOut
{	
	float3 Color : COLOR;
	float4 PosH : SV_Position;
};

VertexOut main(VertexIn vIn)
{
	VertexOut vOut;
	vOut.PosH = mul(float4(vIn.Pos, 1.0f), mul(model, viewProjXM));
	vOut.Color = vIn.Color;
	return vOut;
}