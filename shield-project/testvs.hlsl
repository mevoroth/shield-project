struct VOut
{
	float4 pos : SV_Position;
	/*float4 color : COLOR;*/
};

cbuffer WorldViewProjectionMatrix : register(b0)
{
	matrix WVPMat;
};

float4 main(float4 Pos : SV_Position/*, float4 Color : COLOR*/) : SV_Position
{
	Pos.x *= 0.5;
	Pos.y *= 0.5;
	Pos.z *= 0.5;
	matrix mat = WVPMat;
	Pos = mul( Pos, WVPMat );
	return Pos;
}
