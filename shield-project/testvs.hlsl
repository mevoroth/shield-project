struct VIn
{
	float4 pos : SV_Position;
	float4 norm : NORMAL;
	/*float4 color : COLOR;*/
};

struct VOut
{
	float4 pos : SV_Position;
	float4 norm : NORMAL;
	/*float4 color : COLOR;*/
};

cbuffer WorldViewProjectionMatrix : register(b0)
{
	matrix WVPMat;
};

VOut main(VIn input/*, float4 Color : COLOR*/)
{
	input.pos.x *= 0.5;
	input.pos.y *= 0.5;
	input.pos.z *= 0.5;
	input.pos = mul( input.pos, WVPMat );
	return input;
}
