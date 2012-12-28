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
	output.pos.x *= 0.5;
	output.pos.y *= 0.5;
	output.pos.z *= 0.5;
	output.pos = mul( output.pos, WVPMat );
	output.norm = input.norm;
	//output.norm = float4(0.0f,0.f,1.f,1.f);
	return output;
}
