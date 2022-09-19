#pragma once
#include "Std.h"

class DxState
{
public:
	static ID3D11SamplerState* g_pDefaultSSWrap;
	static ID3D11SamplerState* g_pDefaultSSMirror;

	static ID3D11RasterizerState* g_pDefaultRSWireFrame;
	static ID3D11RasterizerState* g_pDefaultRSSolid;

	static ID3D11BlendState* g_pDefaultBS;

	static bool SetState(ID3D11Device* pd3dDevice);
	static bool Release();
};

