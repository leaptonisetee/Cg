struct VERT_IN
{
	float4 pos : POSITION0;
	float4 normal : NORMAL;
	float4 color : COLOR0;
};

struct FRAG_IN
{
	float4 pos : SV_POSITION;
	float4 worldPos : TEXCOORD0;
	float4 normal : NORMAL;
	float4 color : COLOR;
};

cbuffer ConstBuffer : register(b0)
{
	float4x4 wvpMatrix;
	float4x4 worldMatrix;
}

FRAG_IN main(VERT_IN input)
{
	FRAG_IN output = (FRAG_IN)0;

	output.pos = mul(input.pos, wvpMatrix);
	output.worldPos = mul(input.pos, worldMatrix);
	output.normal = normalize(mul(input.normal, worldMatrix));
	output.color = input.color;

	return output;
}