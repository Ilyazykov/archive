#include "shared.inl"

void PSMain(in float2 iPos : vpos, out float4 oColor : COLOR0)
{
	float2 uv = iPos / reso;
	uv += float2(gPhi, gPsi);
	oColor = tex2D(SampDiffuse, uv);
}

technique T
{
	pass P
	{
		PixelShader = compile ps_3_0 PSMain();
	}
}