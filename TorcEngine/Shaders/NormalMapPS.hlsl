#include "LightCalculations.hlsl"

Texture2D diffuseTexture;
Texture2D normalMapTexture;
SamplerState samplerState;

float3 NormalMapCoordToWorld(float3 sampledNmap,float3 unitTangentW,float3 unitNormalW)
{
	
	float3 normal = 2 * sampledNmap - 1; // This maps the range [0,1] from sampling to [-1,1] for normal vector
	
	// Create TBN basis vectors vectors from vertex shader will be multipled with Mworld so we will only be
	// multipltying TBN base to obtain normals respect to the world space
	
	// Normal vector which already normalized in vertex shader
	float3 N = unitNormalW;
	// T - (proj of T onto N) (T*N)N to make sure T and N are orthonormal
	float3 T = normalize(unitTangentW - dot(unitTangentW, N)*N);
	float3 B = cross(N, T);
	
	float3x3 TBN = float3x3(T, B, N);
	
	float3 mappedNormalW = mul(normal, TBN);
	
	return mappedNormalW;
	
	
	
}

float4 main(float3 PosW : Pos, float3 NormalW : n, float3 eyePos : EyePosition, float3 tangentW : Tangent, float2 tc : TexCoord) :	SV_TARGET
{
		NormalW = normalize(NormalW);
		
	
	    float3 normalMapSample = normalMapTexture.Sample(samplerState, tc);
		float3 newNormal = NormalMapCoordToWorld(normalMapSample, tangentW, NormalW);
		float3 toEyeW = normalize(eyePos - PosW);
		float distToEye = length(eyePos - PosW);
		float4 texColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
	//texColor = tex.Sample
	// Start with a sum of zero. 
		float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
   
		float4 A, D, S;
	//Contribution from Directional Light
		ComputeDirectionalLight(toEyeW, newNormal, A, D, S);
		ambient += A;
		diffuse += D;
		spec += S;
	//Contribution from Point light
		ComputePointLight(toEyeW, newNormal, PosW, A, D, S);
		ambient += A;
		diffuse += D;
		spec += S;
		ComputeSpotLight(toEyeW, newNormal, PosW, A, D, S);
		ambient += A;
		diffuse += D;
		spec += S;
	//Final color of the pixel
	
		float4 litColor = (ambient + diffuse) * diffuseTexture.Sample(samplerState, tc) + spec;
	
	//float fogLerp = saturate((distToEye - 15.0f) / 175.0f);
	//float4 fogColor = float4(0.75f, 0.75f, 0.75f, 1.0f);
	
	//litColor = lerp(litColor, fogColor, fogLerp);
		litColor.a = diffuseTexture.Sample(samplerState, tc).a * m_diffuse.a;

		return litColor;
	}