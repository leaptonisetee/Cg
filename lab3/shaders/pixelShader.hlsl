struct FRAG_IN
{
	float4 pos : SV_POSITION;
	float4 worldPos : TEXCOORD0;
	float4 normal : NORMAL;
	float4 color : COLOR;
};

struct MaterialData
{
	float4 emissive;
	float diffuse;
	float ambient;
	float specular;
	float specularPower;
};

struct PointLightData
{
	float4 position;
	float4 color;
	float3 attenuation;
	float _padding;
};

struct LightResult
{
	float4 diffuse;
	float4 specular;
};

cbuffer ConstBuffer : register(b0)
{
	MaterialData material;
	PointLightData pointLight;
	float3 ambientLight;
	float ambientLightStrength; 
	float4 cameraPosition;
}

float doAttenuation(float d)
{
	return 1.0f / (pointLight.attenuation.x + pointLight.attenuation.y * d + pointLight.attenuation.z * d * d);
}

float4 doDiffuse(float3 L, float3 N)
{
	float NdotL = max(0, dot(N, L));
	return pointLight.color * NdotL;
}

float4 doSpecular(float3 V, float3 L, float4 N)
{
	float3 R = normalize(reflect(-L, N));
	float RdotV = max(0, dot(R, V));
	return pointLight.color * pow(RdotV, material.specularPower);
}

LightResult doLighting(float4 P, float4 N)
{
	float3 V = normalize(cameraPosition - P).xyz;

	float3 L = (pointLight.position - P).xyz;
	float distance = length(L);
	L = L / distance;

	float attenuation = doAttenuation(distance);

	LightResult result;
	result.diffuse = doDiffuse(L, N) * attenuation;
	result.specular = doSpecular(V, L, N) * attenuation;

	return result;
}

float4 main(FRAG_IN input) : SV_Target
{
	LightResult lit = doLighting(input.worldPos, normalize(input.normal));

	float4 emissive = material.emissive;
	float4 ambient = material.ambient * float4(ambientLight, 1.0f) * ambientLightStrength;
	float4 diffuse = material.diffuse * lit.diffuse;
	float4 specular = material.specular * lit.specular;

	return (emissive + ambient + diffuse + specular) * input.color;
}