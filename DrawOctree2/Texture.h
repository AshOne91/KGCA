#pragma once
#include "Std.h"
class Texture
{
public:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
public:
	ID3D11Resource* _texture = nullptr;
	ID3D11ShaderResourceView* _pTextureSRV = nullptr;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	HRESULT Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, const std::wstring& name);
};

