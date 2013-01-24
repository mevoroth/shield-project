Texture2D txDiffuse : register( t0 );
SamplerState samLinear : register( s0 );

struct PIn
{
	float4 pos : SV_Position;
	float2 tex : TEXCOORD0;
};

float4 PS( PIn input ) : SV_TARGET
{
	float4 color = txDiffuse.Sample( samLinear, input.tex );
	color.r *= 0.7f;
	if (color.r == 0.f)
	{
		color.a = 0.f;
	}
	else
	{
		color.a = (color.r + color.g + color.b)/3.f;
		//color.a = 0.7f;
	}
	return color;
}
