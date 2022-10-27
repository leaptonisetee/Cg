struct VERT_IN
{
	float4 pos : POSITION0;
	float4 normal : NORMAL;
	float4 col : COLOR0;
};

struct FRAG_IN
{
	float4 pos : SV_POSITION;
	float4 col : COLOR;
};

cbuffer ConstBuffer : register(b0)
{
	float4x4 wvpMatrix;
}

FRAG_IN main(VERT_IN input)
{
	FRAG_IN output = (FRAG_IN)0;

	output.pos = mul(input.pos, wvpMatrix);
	output.col = input.col;

	return output;
}