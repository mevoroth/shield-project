struct VIn
{
	float4 pos : SV_Position;
	float4 norm : NORMAL;
	/*float4 color : COLOR;*/
};

struct PIn
{
	float4 pos : SV_Position;
	float4 norm : NORMAL;
};

cbuffer WorldViewProjectionMatrix : register(b0)
{
	matrix WVPMat;
};

PIn VS( VIn input )
{
	PIn output = (PIn)0;
	output.pos = input.pos;
	output.pos.x *= 0.5;
	output.pos.y *= 0.5;
	output.pos.z *= 0.5;
	output.pos = mul( output.pos, WVPMat );
	output.norm = float4(0.0f,0.f,1.f,1.f);
	return output;
}
