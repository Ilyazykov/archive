#include "shared.inl"

float2 Project(float2 p, float phi, float psi)
{
	psi+=M_PI;
	float2 result = p;
	if(IsInSemisphere(p.x,p.y))
	{
		float2 tmp = FishEyeToSemisphere(p);
		result = float2(((tmp.y-psi)/(-2*M_PI)-0.25)*cos(tmp.x+phi)+0.5, ((tmp.y-psi)/(-2*M_PI)-0.25)*sin(tmp.x+phi)+0.5);
	}
	return result;
}

void PSMain(in float2 iPos : vpos, out float4 oColor : COLOR0)
{
	float2 uv = Project(iPos / reso, gPhi, gPsi);
	oColor = tex2D(SampDiffuse, uv);
}

technique T
{
	pass P
	{
		PixelShader = compile ps_3_0 PSMain();
	}
}