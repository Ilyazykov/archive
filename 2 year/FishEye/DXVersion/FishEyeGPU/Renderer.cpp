#include "StdAfx.h"
#include "Renderer.h"

CRenderer::CRenderer()
{

}

CRenderer::~CRenderer()
{
}

void CRenderer::Init(HWND pHWnd)
{
	D3DPRESENT_PARAMETERS D3DPP = 
	{
		0, // set proper width
		0, // set proper height
		D3DFMT_X8R8G8B8,
		//D3DFMT_A2B10G10R10,
		2,
		D3DMULTISAMPLE_NONE,
		0,
		D3DSWAPEFFECT_DISCARD,
		NULL, // set proper hwnd
		TRUE, // windowed/not
		FALSE,
		D3DFMT_D24S8,
		0,
		0,
		D3DPRESENT_INTERVAL_DEFAULT
		//D3DPRESENT_INTERVAL_ONE // vsync
	};
	
	mD3D = Direct3DCreate9(D3D_SDK_VERSION);
	mD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, pHWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &D3DPP, &mDevice);
}

void CRenderer::Begin()
{
	mDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0, .0f, 0);	
	mDevice->BeginScene();
}

void CRenderer::End()
{
	mDevice->EndScene();
	mDevice->Present(NULL, NULL, NULL, NULL);
}

void CRenderer::RenderFSQ()
{
	mDevice->SetFVF(D3DFVF_XYZRHW);
	const int WINDOW_WIDTH = 1024;
	const int WINDOW_HEIGHT = 1024;
	float pTriangle[] =
	{
		.0f, .0f, .0f, .0f,
		WINDOW_WIDTH, .0f, .0f, .0f,
		.0f, WINDOW_HEIGHT, .0f, .0f,
		WINDOW_WIDTH, WINDOW_HEIGHT, .0f, .0f
	};
	mDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pTriangle, 4 * 4);
	
}

bool CRenderer::CreateEffectFromFile(const std::string& pFilename, ID3DXEffect*& rEffect)
{
	D3DXCreateEffectFromFileA(mDevice, pFilename.c_str(), NULL, NULL, NULL, NULL, &rEffect, NULL);
	return true;
}