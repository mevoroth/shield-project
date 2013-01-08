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
	if (color.r == 0.f /*&& color.g == 0.f && color.b == 0.f*/)
	{
		/*color.r = 1.f;
		color.g = 1.f;
		color.b = 1.f;*/
		color.a = 0.f;
	}
	return color;
}
