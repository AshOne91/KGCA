#include "Texture.h"

HRESULT Texture::Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, const std::wstring& name)
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(
		pd3dDevice,
		pImmediateContext,
		name.c_str(),
		(ID3D11Resource**)&_pTexture,
		&_pTextureSRV);

	if (FAILED(hr))
	{
		hr = DirectX::CreateDDSTextureFromFile(
			pd3dDevice,
			pImmediateContext,
			name.c_str(),
			(ID3D11Resource**)&_pTexture,
			&_pTextureSRV);
		if (FAILED(hr))
		{
			return hr;
		}
	}

	if (_pTexture != nullptr)
	{
		_pTexture->GetDesc(&_Desc);
	}
	return hr;
}

void Texture::Apply(ID3D11DeviceContext* pImmediateContext, UINT iSlot)
{
	pImmediateContext->PSSetShaderResources(iSlot, 1, &_pTextureSRV);
}

bool Texture::Release()
{
	if (_pTexture) _pTexture->Release();
	if (_pTextureSRV) _pTextureSRV->Release();
	_pTexture = nullptr;
	_pTextureSRV = nullptr;
	return true;
}