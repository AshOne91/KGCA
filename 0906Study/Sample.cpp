#include "Sample.h"
bool Sample::Init()
{
	std::wstring shaderfilename = L"../../data/shader/DefaultShape.txt";

	for (int iObj = 0; iObj < 10; iObj++)
	{
		BaseObject* pObj = new BaseObject;
		pObj->Create(_pd3dDevice,
			_pImmediateContext,
			shaderfilename,
			L"../../data/KGCABK.bmp");
		_ObjectList.push_back(pObj);
	}
	for (int iObj = 0; iObj < 10; iObj++)
	{
		BaseObject* pObj = new BaseObject;
		pObj->Create(_pd3dDevice,
			_pImmediateContext,
			shaderfilename,
			L"../../data/bitmap1.bmp");
		_ObjectList.push_back(pObj);
	}


	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;// 최근점 필터링
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	HRESULT hr = _pd3dDevice->CreateSamplerState(&sd, &g_pDefaultSS);
	return true;
}
bool Sample::Frame()
{
	for (int iObj = 0; iObj < _ObjectList.size(); iObj++)
	{
		_ObjectList[iObj]->Frame();
	}
	return true;
}
bool Sample::Render()
{
	_pImmediateContext->PSSetSamplers(0, 1, &g_pDefaultSS);
	for (int iObj = 0; iObj < _ObjectList.size(); iObj++)
	{
		_ObjectList[iObj]->Render();
	}
	return true;
}
bool Sample::Release()
{
	g_pDefaultSS->Release();
	for (int iObj = 0; iObj < _ObjectList.size(); iObj++)
	{
		_ObjectList[iObj]->Release();
		delete _ObjectList[iObj];
	}
	return true;
}

GAME_RUN(GameTest, 1024, 768)
