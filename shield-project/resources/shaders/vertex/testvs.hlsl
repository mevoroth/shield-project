struct VIn
{
	float4 pos : SV_Position;
	float4 norm : NORMAL;
	float2 tex : TEXCOORD0;
	/*float4 color : COLOR;*/
};

struct VOut
{
	float4 pos : SV_Position;
	float4 norm : NORMAL;
	float2 tex : TEXCOORD0;
};

cbuffer WorldViewProjectionMatrix : register(b0)
{
	matrix WVPMat;
};

VOut VS( VIn input )
{
	VOut output = (VOut)0;
	output.pos = input.pos;
	output.pos = mul( output.pos, WVPMat );
	output.norm = input.norm;
	output.tex = input.tex;
	return output;
}
