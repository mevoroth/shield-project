struct VIn
{
	float4 pos : SV_Position;
	float4 norm : NORMAL;
	/*float4 color : COLOR;*/
};

float4 main(VIn input) : SV_TARGET
{
	input.norm.w /= 200;
	return input.norm*200;
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}
