#pragma once
#include "Std.h"
class Texture
{
protected:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	ID3D11Texture2D* _pTexture = nullptr;
public:
	ID3D11ShaderResourceView* _pTextureSRV = nullptr;
	D3D11_TEXTURE2D_DESC _Desc;
	ID3D11Texture2D* GetTexture() { return _pTexture; }
	ID3D11ShaderResourceView* GetSRV() { return _pTextureSRV; }
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	HRESULT Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, const std::wstring& name);
};

