#pragma once
#include "Std.h"
class DxState
{
public:
	static ID3D11SamplerState* g_pDefaultSS;
	static ID3D11BlendState* g_pDefaultBS;

	static bool SetState(ID3D11Device* p3d3Device);
	static bool Release();
};

