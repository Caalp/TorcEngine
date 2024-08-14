cbuffer DirectionalLight : register(b0)
{
	float4 d_ambient;
	float4 d_diffuse;
	float4 d_specular;
	float4 d_direction;
	//float padding;
}

cbuffer Material : register(b1)
{
	float4 m_ambient;
	float4 m_diffuse;
	float4 m_specular; // Specular power stored in w component
	float4 m_reflection;
   
}

cbuffer PointLight : register(b2)
{
	float4 p_ambient;
	float4 p_diffuse;
	float4 p_specular;
	float3 p_att;
	float3 p_position;
	float range;
}

cbuffer SpotLight : register(b3)
{
	float4 s_ambient;
	float4 s_diffuse;
	float4 s_specular;
   
	float3 s_att;
	float3 s_position;
	float3 s_direction;

	float s_range;
	float s_spot;
}

cbuffer EffectStatus : register(b4)
{
	bool fogEnabled;
	bool reflactionEnabled;
	bool alphaClipEnabled;
	bool textureUsed;
}

void ComputeDirectionalLight(float3 toEye,
	float3 normal,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec)
{
	// Initialize outputs.
	ambient = float4(0.0f,0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f,0.0f, 0.0f, 0.0f);
	spec = float4(0.0f,0.0f, 0.0f, 0.0f);

	
	float3 lightVec = (float3)-d_direction;

	// Add ambient term.
	ambient = m_ambient * d_ambient;

	
	
	float diffuseFactor = dot(lightVec, normal);

	
	if (diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVec, normal);
		float specFactor = pow(max(dot(v, toEye), 0.0f), m_specular.w );

		diffuse = diffuseFactor * m_diffuse * d_diffuse;
		spec = specFactor * m_specular * d_specular;
	}
}

void ComputePointLight(float3 toEye,
	float3 normal,
	float3 pos,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec)
{
	// initialize outputs to zero
	ambient = float4(0.0f,0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f,0.0f, 0.0f, 0.0f);
	spec = float4(0.0f,0.0f, 0.0f, 0.0f);

	// calculate the vector from surface to eyes
	float3 lightVector = p_position - pos;

	// distance from surface to light

	float d = length(lightVector);

	// Range of the point light which is also good for performance
	if (d > range)
		return;

	lightVector /= d; // normalize the light vector

	ambient = m_ambient * p_ambient;

	float diffuseFactor = dot(lightVector, normal);
	
	// if it is small then 0 no diffuse light
	if (diffuseFactor > 0.0f)
	{
		// reflection function basically calculates I-2dot(n,I)n
		float3 v = reflect(-lightVector, normal);
		//Lamberts cosine Law 
		float specFactor = pow(max(dot(v, toEye), 0.0f), m_specular.w); // SpecPower should be always >= 1

		diffuse = diffuseFactor * m_diffuse * p_diffuse;
		spec = specFactor * m_specular * p_specular;
	}

	// Attenuation with better function instead of d^2 
	float att = 1.0f / dot(p_att, float3(1.0f, d, d * d));
	
	diffuse *= att;
	spec *= att;

}

void ComputeSpotLight(float3 toEye, float3 normal, float3 pos,
						out float4 ambient, out float4 diffuse, out float4 spec)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightVector = s_position - pos;


	float d = length(lightVector);
	if (d > s_range)
		return;

	lightVector /= d; // normalize the light vector

	ambient = m_ambient * s_ambient;

	float diffuseFactor = dot(lightVector, normal);
	
	// if it is small then 0 no diffuse light
	if (diffuseFactor > 0.0f)
	{
		// reflection function basically calculates I-2dot(n,I)n
		float3 v = reflect(-lightVector, normal);
		//Lamberts cosine Law 
		float specFactor = pow(max(dot(v, toEye), 0.0f), m_specular.w); // SpecPower should be always >= 1

		diffuse = diffuseFactor * m_diffuse * s_diffuse;
		spec = specFactor * m_specular * s_specular;
	}
	// find the spot factor in order to use for attenuation
	float spot = pow(max(dot(-lightVector, s_direction), 0.0f), s_spot);
	// Attenuation with better function instead of d^2 
	float att = spot / dot(s_att, float3(1.0f, d, d * d));
	ambient *= spot;
	diffuse *= att;
	spec *= att;
}