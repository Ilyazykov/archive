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
	return float2(atan2(p.y-0.5, p.x-0.5), (0.5 - sqrt((p.x-0.5)*(p.x-0.5)+(p.y-0.5)*(p.y-0.5)))*M_PI);
} 


bool IsInSemisphere(float x, float y)
{
	return ((((x-0.5f)*(x-0.5f)+(y-0.5f)*(y-0.5f))<0.25f) || (((x-0.5f)*(x-0.5f)+(y-0.5f)*(y-0.5f))==0.25f));
}

float gPhi;
float gPsi;

float2 reso;