Texture2D txDiffuse : register( t0 );
SamplerState samLinear : register( s0 );

struct PIn
{
	float4 pos : SV_Position;
	float4 norm : NORMAL;
	float2 tex : TEXCOORD0;
};

float4 PS( PIn input ) : SV_TARGET
{
	float dotprod = -input.norm.y/length(input.norm);
	if (dotprod < 0.f)
	{
		dotprod = 0.f;
	}
	float4 color = txDiffuse.Sample( samLinear, input.tex );
	
	float Ia = 0.4f;
	float Id = 0.5f*max(0.f, dotprod);
	float Is = 0.9f*pow(max(0.f, dotprod), 1.f);

	color = color*Ia + color*Id + color*Is;
	color.w = 1.f;

	return color;
}
