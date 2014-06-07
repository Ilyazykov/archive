#define M_PI 3.14
Texture TexDiffuse;

sampler SampDiffuse = sampler_state
{
	Texture = (TexDiffuse);
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
};

float2 FishEyeToSemisphere(float2 p)
{
	return float2(atan2(p.x-0.5, p.y-0.5), (0.5 - sqrt((p.x-0.5)*(p.x-0.5)+(p.y-0.5)*(p.y-0.5)))*M_PI);
} 

bool IsInSemisphere(float2 p)
{
	return (((p.x-0.5f)*(p.x-0.5f)+(p.y-0.5f)*(p.y-0.5f))>0.25f);
}

float3 TopCoordinate(float2 angle)
{
	float3 vec;
	vec[1] = abs(1/( tan(angle[1])*sqrt(tan(angle[0])*tan(angle[0])+1)));
	vec[0] = abs(tan(angle[0])/(tan(angle[1])*sqrt(tan(angle[0])*tan(angle[0])+1)));

	if (sin(angle[0]) < 0) 
	{
		vec[0] = -vec[0];
	}

	if (cos(angle[0]) < 0) 
	{
		vec[1] = -vec[1];
	}

	if (sin(angle[1])>0) vec[2] = 1;
	else vec[2] = -1;

	return vec;
}

void turn(inout float2 turnAngle, inout float3 vec)
{
	turnAngle[1] = -turnAngle[1];

	float x = vec[0];	float y = vec[1];	float z = vec[2];

	vec[1] = y*cos(turnAngle[1]) + z*sin(turnAngle[1]);
	vec[2] = -y*sin(turnAngle[1]) + z*cos(turnAngle[1]);


	x = vec[0];	y = vec[1];	z = vec[2];

	vec[0] = x*cos(turnAngle[0]) - y*sin(turnAngle[0]);
	vec[1] = x*sin(turnAngle[0]) + y*cos(turnAngle[0]);
	

	float lol;
	if (vec[2] > 0) lol = 1/vec[2];
	else lol = -1/vec[2];
	vec *= lol;
}

void normaAngle(inout float2 angle)
{
	while (angle[1] < M_PI/2) angle[1] +=M_PI*2;
	while (angle[1] >= 2*M_PI+M_PI/2) angle[1] -=M_PI*2;

	if (angle[1] > M_PI/2+M_PI)
	{
		angle[1] = M_PI - angle[1];
		angle[0] += M_PI*2;
	}

	while (angle[0] >= 7 * M_PI / 4) angle[0] -= M_PI*2;
	while (angle[0] < - M_PI / 4) angle[0] += M_PI*2;
}

bool computAngle(const float2 p, float2 angle)
{
	float realX = p.y - 0.5f;
	float realY = p.x - 0.5f;
	float temp = sqrt(realX*realX+realY*realY);

	angle[0] = atan2(realY, realX);

	angle[1] = M_PI*(0.5 - temp);

	return true;
}

void VecToAngle(const float3 vec, out float2 angle)
{
	angle[0] = atan(vec[0]/vec[1]);
	if (vec[1]<0) angle[0] += M_PI;
	float temp = sqrt(vec[1]*vec[1]+vec[0]*vec[0]);
	angle[1] = atan(1/temp);
	if (vec[2]<0) angle[1] += M_PI;
}

float gPhi;
float gPsi;

float2 reso;