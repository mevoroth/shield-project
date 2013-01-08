struct VIn
{
	float4 pos : SV_Position;
	float2 tex : TEXCOORD0;
	/*float4 color : COLOR;*/
};

struct VOut
{
	float4 pos : SV_Position;
	float2 tex : TEXCOORD0;
};

VOut VS( VIn input )
{
	VOut output = (VOut)0;
	output.pos = input.pos;
	output.tex = input.tex;
	return output;
}
