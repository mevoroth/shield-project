struct PIn
{
	float4 pos : SV_Position;
	float4 norm : NORMAL;
};

float4 PS( PIn input ) : SV_TARGET
{
	input.norm.x = abs(input.norm.x);
	input.norm.y = abs(input.norm.y);
	input.norm.z = abs(input.norm.z);
	input.norm.w = 1.f;
	return input.norm;
	return float4(1.0f, 0.0f, 0.0f, 1.0f);
}
