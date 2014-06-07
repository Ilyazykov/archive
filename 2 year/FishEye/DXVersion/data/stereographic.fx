#include "shared.inl"

void VecToAngle1(const float3 vec, out float2 angle)
{
    angle[0] = atan2(vec[0],vec[1]);
    float temp = sqrt(vec[1]*vec[1]+vec[0]*vec[0]);
    angle[1] = atan(1/temp);
    if (vec[2]<0)
    {
        angle[1] += M_PI;
        angle[0] += M_PI;
    }
}

float2 Project(float2 p, float phi, float psi)
{
	if (IsInSemisphere(p)) return float2(0,0);
	
	float2 tmp = FishEyeToSemisphere(p);
	float2 angle = tmp;
	
	float3 vec = TopCoordinate(angle);
	float2 turnAngle = float2(phi, psi);
	
	turn(turnAngle, vec);
	VecToAngle1(vec, angle);
	
	angle[1] = -angle[1] + M_PI/2;
	
	float step = (0.5*angle[1])/(M_PI);
	
	float x = sin(angle.xy)*step;
    float y = cos(angle.xy)*step;

    x+=0.5;
    y+=0.5; 
	
	return float2(x,y);
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