
//#pragma pack_matrix( row_major )
cbuffer CBuf : register(b0)
{
	matrix model;
	matrix worldInverseTransform;
};

cbuffer CameraBuffer : register(b1)
{
	matrix viewXM;
	matrix projXM;
	matrix viewProjXM;
	float3 cameraPos;
}