#include "TransformBufferVar.hlsl"

struct VertexIn
{
	float4 PosL2 : Position2;
	float3 PosL : Position;
	float3 NormalL : Normal;
	float3 TangentL: Tangent;
	float2 texCoordinate : TexCoord;
	float tte1 : test;
	float2x2 t2 : t2;
	uint t13 : ut3;
	matrix t14 : mt;
	min16float  obj : boolTest;
};

struct VertexOut
{
   
	float3 PosW : Pos;
	float3 NormalW : n;
	float3 eyePos : EyePosition;
	float3 tangentW : Tangent;
	float2 txCoord : TexCoord;
	float4 PosH : SV_POSITION;
};
VertexOut main(VertexIn vin)
{
	VertexOut vout;
	vout.PosW = mul(float4(vin.PosL, 1.0f), model);
	vout.NormalW = mul(vin.NormalL, (float3x3) worldInverseTransform);
	vout.tangentW = mul(vin.TangentL, (float3x3)model);
	vout.PosH = mul(float4(vin.PosL, 1.0f), model*viewXM*projXM);
	vout.txCoord = vin.texCoordinate;
	vout.eyePos = cameraPos;
  
	return vout;
}