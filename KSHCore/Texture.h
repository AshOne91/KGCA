#pragma once
#include "Std.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"

#ifdef _DEBUG
#pragma comment(lib, "DirectXTK_d.lib")
#else
#pragma comment(lib, "DirectXTK_r.lib")
#endif


class Texture
{
public:
	ID3D11Texture2D* _pTexture = nullptr;
	ID3D11ShaderResourceView* _pTextureSRV = nullptr;
	D3D11_TEXTURE2D_DESC _Desc;

public:
	HRESULT Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, const std::wstring& name);
	void Apply(ID3D11DeviceContext* pImmediateContext, UINT iSlot = 0);
	bool Release();
};

