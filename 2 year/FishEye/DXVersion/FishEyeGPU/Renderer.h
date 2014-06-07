#pragma once
#include "StdAfx.h"

class CRenderer
{
	public:
		CRenderer();
		~CRenderer();
		
		void Init(HWND pHWnd);
		void Begin();
		void End();
		void RenderFSQ();
		
		bool CreateEffectFromFile(const std::string& pFilename, ID3DXEffect*& rEffect);
		
	//protected:
		IDirect3D9* mD3D;
		IDirect3DDevice9* mDevice;
};
