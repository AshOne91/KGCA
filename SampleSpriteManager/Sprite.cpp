#include "Sprite.h"

HRESULT Sprite::Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring name)
{
	std::wstring shaderfilename = L"../../data/shader/DefaultShapeMask.txt";
	std::wstring mapshader = L"../../data/shader/DefaultShape.txt";
	Texture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");

	Create(pd3dDevice,
		pImmediateContext,
		shaderfilename,
		L"../../data/bitmap1.bmp");
	SetMask(pMaskTex);
	_fSpeed = 300.0f;
	return S_OK;
}