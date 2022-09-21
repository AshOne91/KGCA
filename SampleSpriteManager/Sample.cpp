#include "Sample.h"
void Sample::AddEffect()
{
	Effect* pEffect = new Effect;
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
bool Sample::Init()
{
	I_Sprite.SetDevice(_pd3dDevice, _pImmediateContext);
	I_Sprite.Load(L"SpriteInfo.txt");

	std::wstring shaderfilename = L"../../data/shader/DefaultShapeMask.txt";
	std::wstring mapshader = L"../../data/shader/DefaultShape.txt";
	Texture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");

	_pMap = new MapObject;
	_pMap->Create(_pd3dDevice,
		_pImmediateContext,
		mapshader,
		L"../../data/kgcabk.bmp");//"L"../../data/gameHeight.png");
	_pMap->SetRect({ 0, 0,	2000.0f,2000.0f });
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
	return true;
}
bool Sample::Frame()
{
	_pUser->Frame();
	_vCamera = _pUser->_vPos;
	_vCamera.y -= 200.0f;
	_pUser->SetCameraSize({ 800, 800 });
	_pUser->SetCameraPos(_vCamera);
	_pUser->SetPosition(_pUser->_vPos, _vCamera);

	_pMap->SetCameraSize({ 800, 800 });
	_pMap->SetCameraPos(_vCamera);
	_pMap->Frame();

	if (I_Input.GetKey(VK_LBUTTON) == KEY_HOLD)
	{
		AddEffect();
	}

	for (auto iter = _pEffectList.begin();
		iter != _pEffectList.end(); )
	{
		Effect* pEffect = *iter;
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
bool Sample::Render()
{
	if (I_Input.GetKey('V') == KEY_HOLD)
	{
		_pImmediateContext->RSSetState(DxState::g_pDefaultRSWireFrame);
	}
	_pMap->Render();

	_pUser->PreRender();
	_pImmediateContext->PSSetShaderResources(1, 1,
		&_pUser->_pMaskTex->_pTextureSRV);
	_pUser->PostRender();

	for (auto pEffect : _pEffectList)
	{
		pEffect->_pSprite->SetRect(pEffect->_tRect);
		pEffect->_pSprite->SetPosition(pEffect->_vPos);
		pEffect->_pSprite->PreRender();
		_pImmediateContext->PSSetShaderResources(1, 1,
			&pEffect->_pSprite->_pMaskTex->_pTextureSRV);
		pEffect->_pSprite->PostRender();
	}
	return true;
}
bool Sample::Release()
{
	for (auto data : _pEffectList)
	{
		delete data;
	}
	_pEffectList.clear();

	_pMap->Release();
	delete _pMap;
	_pMap = nullptr;

	_pUser->Release();
	delete _pUser;
	_pUser = nullptr;

	/*_pObject->Release();
	delete _pObject;
	_pObject = nullptr;*/
	return true;
}

GAME_RUN(TSampleTexture, 800, 600)