#include "shared.inl"

// нахождение координат точки3D при пересечении с верхней гранью при заданном угле

float2 pointTopBottom(float3 vec)
{
	float x, y;

	if (vec[2] > 0)	x = 0.375f + vec[0]/8.0f; //если верхняя
	else x = 0.874f - vec[0]/8.0f; //если нижняя

	y = (3.0f + vec[1])/6.0f;
	
	return float2(x, y);
}

void commonComput(out float x3d, out float y3d, float2 angle)
{
	x3d = tan(angle[0])/2;
	y3d = tan(angle[1])*sqrt(tan(angle[0])*tan(angle[0])+1)/2;
}

float2 pointFront(float2 angle)
{
	float x; float y;
	x = 0.25f;		x += 0.125f;	
	y = 2.0f/3.0f;	y += 1.0f/6.0f;

	float x3d = 0; float y3d = 0;
	commonComput(x3d, y3d, angle);
	x3d /= 4;
	y3d /= 3;

	x += x3d;
	y += y3d;

	return float2(x, y);
}

float2 pointRight(float2 angle)
{
	angle[0] -= 1 * M_PI/2;
	float x; float y;
	x = 0.5f;		x += 0.125f;
	y = 2.0f/3.0f;	y -= 1.0f/6.0f;

	float x3d; float y3d;
	commonComput(x3d, y3d, angle);
	
	x3d /= 3;
	y3d /= 4;

	x += y3d;
	y -= x3d;

	return float2(x, y);
}

float2 pointBack(float2 angle)
{
	angle[0] -= 2 * M_PI/2; 
	float x; float y;
	x = 0.5f;		x -= 0.125f;
	y = 1.0f/3.0f;	y -= 1.0f/6.0f;

	float x3d; float y3d;
	commonComput(x3d, y3d, angle);										
	
	x3d /= 4;
	y3d /= 3;

	x -= x3d;
	y -= y3d;

	return float2(x, y);
}

float2 pointLeft(float2 angle)
{
	angle[0] -= 3 * M_PI/2; 
	float x; float y;
	x = 0.25f;		x -= 0.125f;
	y = 1.0f/3.0f;	y += 1.0f/6.0f;

	float x3d; float y3d;
	commonComput(x3d, y3d, angle);

	x3d /= 3;
	y3d /= 4;

	x -= y3d;
	y += x3d;

	return float2(x, y);
}

float2 Project(const float2 p, float phi, float psi)
{
	if (IsInSemisphere(p)) return float2(0,0);
	
	float2 tmp = FishEyeToSemisphere(p);
	float2 angle = tmp;

	float3 vec = TopCoordinate(angle);
	float2 ThePoint;
	float2 turnAngle = float2(phi, psi);// угол направления взгляда

	turn(turnAngle, vec);
	VecToAngle(vec, angle);

	normaAngle(angle); // нормализует угол
	if (abs(vec[0]) < 1 && abs(vec[1]) < 1)
	{
		ThePoint = pointTopBottom(vec);
		return ThePoint;
	}
	else
	{
		if		(angle[0] < M_PI/4)		ThePoint = pointFront(angle);
		else if	(angle[0] < 3 * M_PI / 4)	ThePoint = pointRight(angle);
		else if	(angle[0] < 5 * M_PI / 4)	ThePoint = pointBack(angle);
		else							ThePoint = pointLeft(angle);
		return ThePoint;
	}

	return float2(0,0);
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