#include "Sprite.h"

bool Sprite::Load(ID3D11Device* pd3dDevice,// 디바이스 객체
	ID3D11DeviceContext* pImmediateContext, const std::wstring& name)
{
	/*std::wstring shaderfilename = L"../../data/shader/DefaultShapeMask.txt";
	std::wstring mapshader = L"../../data/shader/DefaultShape.txt";
	Texture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");

	Create(pd3dDevice,
		pImmediateContext,
		shaderfilename,
		L"../../data/bitmap1.bmp");
	SetMask(pMaskTex);
	_fSpeed = 300.0f;
	return S_OK;*/
	Texture* pMaskTex = I_Tex.Load(_szMaskTexturePath);

	if (!Create(pd3dDevice, pImmediateContext, _szShaderPath, _szTexturePath))
	{
		return false;
	}

	SetMask(pMaskTex);
	_fSpeed = 300.0f;
	return true;
}

bool SpriteTexture::Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, const std::wstring& name)
{
	_pTexArray.resize(_texArray.size());
	for (int iTex = 0; iTex < _texArray.size(); ++iTex)
	{
		_pTexArray[iTex] = I_Tex.Load(_texArray[iTex]);
	}

	return Sprite::Load(pd3dDevice, pImmediateContext, name);
}
