#include "pch.h"
#include "SceneInGame.h"
#include "Input.h"
#include "DxState.h"

static TVector2 vSize = { 1024, 768 };

void SceneInGame::AddProjectile(TVector2 pos)
{
	Projectile2D* pEffect = new Projectile2D;
	pEffect->_pSprite = I_Sprite.GetPtr(L"rtProjectile");
	pEffect->_fEffectTimer = 0.0f;
	RECT rt = pEffect->_pSprite->_uvArray[0];
	pEffect->_tRect.x1 = rt.left;
	pEffect->_tRect.y1 = rt.top;
	pEffect->_tRect.w = rt.right;
	pEffect->_tRect.h = rt.bottom;

	pEffect->_iIndex = 0;
	pEffect->_fLifeTime = 10.0f;
	pEffect->_vPos = pos;
	pEffect->_fStep = pEffect->_fLifeTime /
		pEffect->_pSprite->_uvArray.size();
	pEffect->_iMaxIndex = pEffect->_pSprite->_uvArray.size();

	pEffect->_pSprite->SetRect(pEffect->_tRect);
	pEffect->_pSprite->SetPosition(pEffect->_vPos);

	pEffect->_rtCollision = pEffect->_pSprite->_rtCollision;
	pEffect->_rtCollision.x1 = pEffect->_vPos.x;
	pEffect->_rtCollision.y1 = pEffect->_vPos.y;
	_Projectile.push_back(pEffect);
}

void SceneInGame::AddEffect()
{
	Effect2D* pEffect = new Effect2D;
	UINT iEffect = rand() % 3;
	if (iEffect == 0)
		pEffect->_pSprite = I_Sprite.GetPtr(L"rtExplosion");
	else if (iEffect == 1)
		pEffect->_pSprite = I_Sprite.GetPtr(L"rtBomb");
	else
		pEffect->_pSprite = I_Sprite.GetPtr(L"rtClash");
	pEffect->_fEffectTimer = 0.0f;
	RECT rt = pEffect->_pSprite->_uvArray[0];
	pEffect->_tRect.x1 = rt.left;
	pEffect->_tRect.y1 = rt.top;
	pEffect->_tRect.w = rt.right;
	pEffect->_tRect.h = rt.bottom;

	pEffect->_iIndex = 0;
	pEffect->_fLifeTime = 1.0f;
	pEffect->_vPos = { (float)I_Input._ptPos.x,(float)I_Input._ptPos.y };
	pEffect->_fStep = pEffect->_fLifeTime /
		pEffect->_pSprite->_uvArray.size();
	pEffect->_iMaxIndex = pEffect->_pSprite->_uvArray.size();

	pEffect->_pSprite->SetRect(pEffect->_tRect);
	pEffect->_pSprite->SetPosition(pEffect->_vPos);

	pEffect->_rtCollision = pEffect->_pSprite->_rtCollision;
	pEffect->_rtCollision.x1 = pEffect->_vPos.x;
	pEffect->_rtCollision.y1 = pEffect->_vPos.y;
	_pEffectList.push_back(pEffect);
}

void SceneInGame::AddEffect(float x, float y)
{
	Effect2D* pEffect = new Effect2D;
	UINT iEffect = rand() % 3;
	if (iEffect == 0)
		pEffect->_pSprite = I_Sprite.GetPtr(L"rtExplosion");
	else if (iEffect == 1)
		pEffect->_pSprite = I_Sprite.GetPtr(L"rtBomb");
	else
		pEffect->_pSprite = I_Sprite.GetPtr(L"rtClash");
	pEffect->_fEffectTimer = 0.0f;
	RECT rt = pEffect->_pSprite->_uvArray[0];
	pEffect->_tRect.x1 = rt.left;
	pEffect->_tRect.y1 = rt.top;
	pEffect->_tRect.w = rt.right;
	pEffect->_tRect.h = rt.bottom;

	pEffect->_iIndex = 0;
	pEffect->_fLifeTime = 1.0f;
	pEffect->_vPos = { x,y };
	pEffect->_fStep = pEffect->_fLifeTime /
		pEffect->_pSprite->_uvArray.size();
	pEffect->_iMaxIndex = pEffect->_pSprite->_uvArray.size();

	pEffect->_pSprite->SetRect(pEffect->_tRect);
	pEffect->_pSprite->SetPosition(pEffect->_vPos);

	pEffect->_rtCollision = pEffect->_pSprite->_rtCollision;
	pEffect->_rtCollision.x1 = pEffect->_vPos.x;
	pEffect->_rtCollision.y1 = pEffect->_vPos.y;
	_pEffectList.push_back(pEffect);
}

bool SceneInGame::Init()
{
	I_Sprite.Load(L"ui.txt");

	std::wstring shaderfilename = L"../../data/shader/DefaultShapeMask.txt";
	std::wstring mapshader = L"../../data/shader/DefaultShape.txt";
	Texture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");

	_pMap = new MapObject;
	_pMap->Create(_pd3dDevice,
		_pImmediateContext,
		mapshader,
		L"../../data/back_dis.png");//"L"../../data/gameHeight.png");
	_pMap->SetRect({ 0, 0,	2000.0f, 2000.0f });
	_pMap->SetPosition({ 0.0f, 0.0f });

	_pUser = new User2D;
	_pUser->Create(_pd3dDevice, _pImmediateContext,
		L"../../data/shader/DefaultShapeMask.txt",
		L"../../data/bitmap1.bmp");
	_pUser->SetMask(pMaskTex);
	_pUser->_fSpeed = 300.0f;
	_pUser->SetRect({ 90, 2, 40, 60 });
	_pUser->SetPosition({ 0.0f,0.0f });

	_vCamera = _pUser->_vPos;
	//_vCamera.y -= 200.0f;

	for (int iNpc = 0; iNpc < 100; iNpc++)
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
		npc->SetDirection({ randstep(-1.0f, 1.0f),	randstep(-1.0f, 1.0f) });

		npc->SetCameraPos(_vCamera);
		npc->SetPosition({ randstep(-900,+900), randstep(-900,+900) });
		npc->SetMask(pMaskTex);
		_pNpcList.push_back(npc);
	}
	return true;
}

bool SceneInGame::Frame()
{
	float fAspectRatio = vSize.y / vSize.x;
	if (I_Input.GetKey(VK_LEFT) == KEY_HOLD)
	{
		vSize.x -= g_fSecondPerFrame * 100.0f;
		vSize.y -= g_fSecondPerFrame * 100.0f * fAspectRatio;
	}
	if (I_Input.GetKey(VK_RIGHT) == KEY_HOLD)
	{
		vSize.x += g_fSecondPerFrame * 100.0f;
		vSize.y += g_fSecondPerFrame * 100.0f * fAspectRatio;
	}
	_pUser->Frame();
	_vCamera = _pUser->_vPos;
	//_vCamera.y -= 200.0f;
	_pUser->SetCameraSize(vSize);
	_pUser->SetCameraPos(_vCamera);
	_pUser->SetPosition(_pUser->_vPos, _vCamera);

	_pMap->SetCameraSize(vSize);
	_pMap->SetCameraPos(_vCamera);
	_pMap->Frame();

	for (auto iter = _pNpcList.begin();
		iter != _pNpcList.end(); iter++)
	{
		Npc2D* npc = *iter;
		npc->SetCameraSize(vSize);
		npc->SetCameraPos(_vCamera);
		npc->Frame();
	}

	if (I_Input.GetKey(VK_LBUTTON) == KEY_PUSH)
	{
		AddProjectile(_pUser->_vPos);
	}

	for (auto iter = _Projectile.begin(); iter != _Projectile.end(); )
	{
		Projectile2D* pEffect = *iter;
		pEffect->_vPos.x = _pUser->_vPos.x;
		if (pEffect->Update() == false)
		{
			delete pEffect;
			iter = _Projectile.erase(iter);
			continue;
		}
		iter++;
	}
	for (auto iter = _Projectile.begin(); iter != _Projectile.end(); iter++)
	{
		for (auto src = _pNpcList.begin(); src != _pNpcList.end();)
		{
			Rect inst;
			if (Collision::RectToRect((*iter)->_rtCollision, (*src)->_rtCollision, inst))
			{
				AddEffect(inst.cx, inst.cy);
				(*src)->Release();
				delete* src;
				src = _pNpcList.erase(src);
			}
			else
			{
				src++;
			}
		}
	}

	for (auto src = _pNpcList.begin(); src != _pNpcList.end();)
	{
		Rect inst;
		if (Collision::RectToRect((*src)->_rtCollision, _pUser->_rtCollision, inst))
		{
			//AddEffect(inst.cx, inst.cy);
			(*src)->Release();
			delete* src;
			src = _pNpcList.erase(src);
			continue;
		}
		bool bFlag = false;
		for (auto dest = _pNpcList.begin(); dest != _pNpcList.end(); )
		{
			Rect npcinst;
			if (src == dest)
			{
				dest++;
				continue;
			}
			if (Collision::RectToRect((*src)->_rtCollision, (*dest)->_rtCollision, npcinst))
			{
				//AddEffect(npcinst.cx, npcinst.cy);
				(*dest)->Release();
				delete* dest;
				bFlag = true;
				dest = _pNpcList.erase(dest);
			}
			else
			{
				dest++;
			}
		}
		if (bFlag)
		{
			(*src)->Release();
			delete* src;
			src = _pNpcList.erase(src);
		}
		else
		{
			src++;
		}
	}

	for (auto iter = _pEffectList.begin();
		iter != _pEffectList.end(); )
	{
		Effect2D* pEffect = *iter;
		if (pEffect->Update() == false)
		{
			delete pEffect;
			iter = _pEffectList.erase(iter);
			continue;
		}
		iter++;
	}

	return true;
}

bool SceneInGame::Render()
{
	if (I_Input.GetKey('V') == KEY_HOLD)
	{
		_pImmediateContext->RSSetState(DxState::g_pDefaultRSWireFrame);
	}
	_pMap->Render();

	for (auto data : _pNpcList)
	{
		data->Render();
	}

	_pUser->PreRender();
	_pImmediateContext->PSSetShaderResources(1, 1,
		&_pUser->_pMaskTex->_pTextureSRV);
	_pUser->PostRender();


	for (auto pEffect : _pEffectList)
	{
		pEffect->_pSprite->SetCameraSize(vSize);
		pEffect->_pSprite->SetCameraPos(_vCamera);
		pEffect->_pSprite->SetRect(pEffect->_tRect);
		pEffect->_pSprite->SetPosition(pEffect->_vPos, _vCamera);
		pEffect->_pSprite->PreRender();
		_pImmediateContext->PSSetShaderResources(1, 1,
			&pEffect->_pSprite->_pMaskTex->_pTextureSRV);
		pEffect->_pSprite->PostRender();
	}

	for (auto projectile : _Projectile)
	{
		projectile->_pSprite->SetCameraSize(vSize);
		projectile->_pSprite->SetCameraPos(_vCamera);
		projectile->_pSprite->SetRect(projectile->_tRect);
		projectile->_pSprite->SetPosition(projectile->_vPos, _vCamera);
		projectile->_pSprite->PreRender();
		_pImmediateContext->PSSetShaderResources(1, 1,
			&projectile->_pSprite->_pMaskTex->_pTextureSRV);
		projectile->_pSprite->PostRender();
	}
	return true;
}

bool SceneInGame::Release()
{
	_pMap->Release();
	delete _pMap;
	_pMap = nullptr;

	_pUser->Release();
	delete _pUser;
	_pUser = nullptr;

	for (auto data : _pNpcList)
	{
		data->Release();
		delete data;
	}

	for (auto data : _pEffectList)
	{
		delete data;
	}
	_pEffectList.clear();

	for (auto data : _Projectile)
	{
		delete data;
	}
	_Projectile.clear();

	return true;
}

void SceneInGame::DrawMiniMap(UINT x, UINT y, UINT w, UINT h)
{
	D3D11_VIEWPORT saveViewPort[15];
	UINT SaveNumView = 1;
	_pImmediateContext->RSGetViewports(&SaveNumView, saveViewPort);

	D3D11_VIEWPORT vp;
	vp.Width = w;
	vp.Height = h;
	vp.TopLeftX = x;
	vp.TopLeftY = y;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	_pImmediateContext->RSSetViewports(1, &vp);
	//TVector2D vCamera = { 0,0 };
	TVector2 vSize = { 2000, 2000 };
	_pMap->SetCameraSize(vSize);
	_pMap->SetCameraPos(_vCamera);
	_pMap->Frame();
	_pMap->Render();
	for (auto npc : _pNpcList)
	{
		npc->SetCameraSize(vSize);
		npc->SetCameraPos(_vCamera);
		npc->Frame();
		npc->Render();
	}
	_pImmediateContext->RSSetViewports(SaveNumView, saveViewPort);
}
