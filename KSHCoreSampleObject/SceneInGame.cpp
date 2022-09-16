#include "SceneInGame.h"
#include "Input.h"

bool SceneInGame::Init()
{
	std::wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	Texture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");

	_pMap = new MapObject;
	_pMap->Create(_pd3dDevice,
		_pImmediateContext,
		shaderfilename,
		L"../../data/kgcabk.bmp");//"L"../../data/gameHeight.png");
	_pMap->SetRect({ 0, 0,	2000.0f,2000.0f });
	_pMap->SetPosition({ -1000.0f, -1000.0f });
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
	_pUser->SetPosition({ 0,0 });


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

		npc->SetCameraPos(_vCamera);
		npc->SetPosition({ randstep(-400,+400), 100.0f });
		npc->SetMask(pMaskTex);
		_pNpcList.push_back(npc);
	}
	return true;
}

bool SceneInGame::Frame()
{
	static Vector2D vSize = { 800, 800 };
	if (I_Input.GetKey(VK_LEFT) == KEY_HOLD)
	{
		vSize.x -= g_fSecondPerFrame * 100.0f;
		vSize.y -= g_fSecondPerFrame * 100.0f;
	}
	if (I_Input.GetKey(VK_RIGHT) == KEY_HOLD)
	{
		vSize.x += g_fSecondPerFrame * 100.0f;
		vSize.y += g_fSecondPerFrame * 100.0f;
	}
	_pUser->SetCameraSize(vSize);
	_pUser->SetCameraPos(_vCamera);
	_pUser->Frame();

	_pMap->SetCameraPos(_vCamera);
	_pMap->SetCameraSize(vSize);
	_pMap->Frame();

	for (int iObj = 0; iObj < _pNpcList.size(); iObj++)
	{
		_pNpcList[iObj]->SetCameraSize(vSize);
		_pNpcList[iObj]->SetCameraPos(_vCamera);
		_pNpcList[iObj]->Frame();
	}
	_vCamera = _pUser->_vPos;
	return true;
}

bool SceneInGame::Render()
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

bool SceneInGame::Release()
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
