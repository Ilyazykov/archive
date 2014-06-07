#include "shared.inl"

void PSMain(in float2 iPos : vpos, out float4 oColor : COLOR0)
{
	oColor = float4(gPhi, gPsi, .0f, .0f);
}

technique T
{
	pass P
	{
		PixelShader = compile ps_3_0 PSMain();
	}
}