#include "Sample.h"
bool Sample::GameDataLoad(const TCHAR* pszLoad)
{
	TCHAR pBuffer[2000] = { 0 };
	TCHAR pTemp[2000] = { 0 };

	int iNumSprite = 0;
	FILE* fp_src;
	_wfopen_s(&fp_src, pszLoad, _T("rt"));
	if (fp_src == NULL) return false;

	_fgetts(pBuffer, _countof(pBuffer), fp_src);
	_stscanf_s(pBuffer, _T("%s%d%s"), pTemp, (unsigned int)_countof(pTemp), &iNumSprite);
	_rtSpriteList.resize(iNumSprite);

	for (int iCnt = 0; iCnt < iNumSprite; iCnt++)
	{
		int iNumFrame = 0;
		_fgetts(pBuffer, _countof(pBuffer), fp_src);
		_stscanf_s(pBuffer, _T("%s %d"), pTemp, (unsigned int)_countof(pTemp), &iNumFrame);
		//m_rtSpriteList[iCnt].resize(iNumFrame);

		RECT rt;
		for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
		{
			_fgetts(pBuffer, _countof(pBuffer), fp_src);
			_stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, (unsigned int)_countof(pTemp),
				&rt.left, &rt.top, &rt.right, &rt.bottom);
			_rtSpriteList[iCnt].push_back(rt);
		}
	}
	fclose(fp_src);
	return true;
}
bool Sample::Init()
{
	GameDataLoad(L"SpriteInfo.txt");
	for (int isp = 0; isp < _rtSpriteList.size(); isp++)
	{
		Sprite* pEffect = new Sprite;
		_pSpriteList.push_back(pEffect);
	}
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

	_pObject = new Sprite;
	_pObject->Create(_pd3dDevice,
		_pImmediateContext,
		shaderfilename,
		L"../../data/bitmap1.bmp");
	_pObject->SetMask(pMaskTex);
	_pObject->_fSpeed = 300.0f;
	RECT rt = _rtSpriteList[0][0];
	Rect tRt;
	tRt.x1 = rt.left;
	tRt.y1 = rt.top;
	tRt.w = rt.right;
	tRt.h = rt.bottom;
	_pObject->SetRect(tRt);
	_pObject->SetPosition({ 400,300 });



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

	static int iSpriteIndex = 1;
	if (I_Input.GetKey('1') == KEY_PUSH)
	{
		iSpriteIndex++;
		if (iSpriteIndex > 2) iSpriteIndex = 0;
	}
	static float eFffectRunning = 1.33f;
	static UINT index = 0;
	static float fEffectTimer = 0.0f;
	fEffectTimer += g_fSecondPerFrame;
	float fStep = eFffectRunning / (float)_rtSpriteList[iSpriteIndex].size();
	if (fEffectTimer >= fStep)
	{
		fEffectTimer -= fStep;
		index++;
	}

	if (index >= _rtSpriteList[iSpriteIndex].size())
	{
		index = 0;
	}
	RECT rt = _rtSpriteList[iSpriteIndex][index];
	Rect tRt;
	tRt.x1 = rt.left;
	tRt.y1 = rt.top;
	tRt.w = rt.right;
	tRt.h = rt.bottom;
	_pObject->SetRect(tRt);
	_pObject->SetPosition({ (float)I_Input._ptPos.x,(float)I_Input._ptPos.y });
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

	_pObject->PreRender();
	_pImmediateContext->PSSetShaderResources(1, 1,
		&_pObject->_pMaskTex->_pTextureSRV);
	_pObject->PostRender();
	return true;
}
bool Sample::Release()
{
	for (int isp = 0; isp < _rtSpriteList.size(); isp++)
	{
		_pSpriteList[isp]->Release();
		delete _pSpriteList[isp];
	}
	_pMap->Release();
	delete _pMap;
	_pMap = nullptr;

	_pUser->Release();
	delete _pUser;
	_pUser = nullptr;

	_pObject->Release();
	delete _pObject;
	_pObject = nullptr;
	return true;
}

GAME_RUN(TSampleTexture, 800, 600)