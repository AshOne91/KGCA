#include "Scene.h"

bool Scene::Create(
	ID3D11Device* pd3dDevice,// 디바이스 객체
	ID3D11DeviceContext* pImmediateContext,
	std::wstring shadername)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmediateContext;
	return true;
}

bool Scene::Init()
{
	std::wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	Texture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");

	_pMap = new MapObject;
	_pMap->Create(_pd3dDevice,
		_pImmediateContext,
		shaderfilename,
		L"../../data/gameHeight.png");

	// user character
   // { 90, 1, 40, 60 } , { 400,300 }
   // -1 ~ +1
	_pUser = new User2D;
	_pUser->Create(_pd3dDevice, _pImmediateContext,
		L"../../data/shader/DefaultShapeMask.txt",
		L"../../data/bitmap1.bmp");
	_pUser->SetMask(pMaskTex);
	_pUser->_fSpeed = 300.0f;
	_pUser->SetRect({ 91, 2, 39, 59 });
	_pUser->SetPosition({ g_rtClient.right / 2.0f,
						   g_rtClient.bottom - 100.0f });


	for (int iNpc = 0; iNpc < 10; iNpc++)
	{
		Npc2D* npc = new Npc2D;
		npc->Create(_pd3dDevice, _pImmediateContext,
			L"../../data/shader/DefaultShapeMask.txt",
			L"../../data/bitmap1.bmp");
		if (iNpc % 2 == 0)
		{
			npc->SetRect({ 46, 62, 68, 79 });
		}
		else
		{
			npc->SetRect({ 115, 62, 37, 35 });
		}
		npc->SetDirection({ randstep(-1.0f, 1.0f),
			randstep(-1.0f, 1.0f) });
		npc->SetPosition({ 100.0f + iNpc * 100.0f, 100.0f });
		npc->SetMask(pMaskTex);
		_pNpcList.push_back(npc);
	}
	return true;
}

bool Scene::Frame()
{
	_pMap->Frame();
	_pUser->Frame();
	for (int iObj = 0; iObj < _pNpcList.size(); iObj++)
	{
		_pNpcList[iObj]->Frame();
	}
	return true;
}

bool Scene::Render()
{
	_pMap->Render();
	for (int iObj = 0; iObj < _pNpcList.size(); iObj++)
	{
		_pNpcList[iObj]->Render();
	}

	_pUser->PreRender();
	_pImmediateContext->PSSetShaderResources(1, 1,
		&_pUser->_pMaskTex->_pTextureSRV);
	_pUser->PostRender();
	return true;
}

bool Scene::Release()
{
	_pMap->Release();
	delete _pMap;

	_pUser->Release();
	delete _pUser;

	for (int iObj = 0; iObj < _pNpcList.size(); iObj++)
	{
		_pNpcList[iObj]->Release();
		delete _pNpcList[iObj];
	}
	return true;
}