#include "SceneTitle.h"

bool SceneTitle::Init()
{
	std::wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	_pMapTitle = new BaseObject;
	_pMapTitle->Create(_pd3dDevice,
		_pImmediateContext,
		shaderfilename,
		L"../../data/kgcabk.bmp");

	_btnStart = new Button;
	_btnStart->Create(_pd3dDevice, _pImmediateContext, shaderfilename, L"../../data/ui/main_start_nor.png");
	_btnStart->Init();

	Texture* pTexture = I_Tex.Load(L"../../data/ui/main_start_nor.png");
	_btnStart->_pCurrentTex = pTexture;
	_btnStart->_pStateList.push_back(pTexture);
	pTexture = I_Tex.Load(L"../../data/ui/main_start_sel.png");
	_btnStart->_pStateList.push_back(pTexture);
	pTexture = I_Tex.Load(L"../../data/ui/main_start_pus.png");
	_btnStart->_pStateList.push_back(pTexture);
	pTexture = I_Tex.Load(L"../../data/ui/main_start_dis.png");
	_btnStart->_pStateList.push_back(pTexture);
	_btnStart->SetRect({ 0, 0,	332.0f, 82.0f });
	_btnStart->SetPosition({ 400.0f, 300.0f });


	_listControl = new ListControl;
	_listControl->Create(_pd3dDevice,
		_pImmediateContext,
		shaderfilename,
		L"../../data/ui/RAINBOW.png");
	_listControl->_pCurrentTex = _listControl->_pTexture;
	_listControl->Init();
	_listControl->SetRect({ 0, 0,	100.0f, 500.0f });
	_listControl->SetPosition({ 60, 300 });
	UINT iNumBtn = 10;
	for (int iBtn = 0; iBtn < iNumBtn; iBtn++)
	{
		Button* btn = new Button;
		btn->Create(_pd3dDevice,
			_pImmediateContext,
			shaderfilename,
			L"../../data/ui/main_plus_dis.png");
		btn->Init();

		Texture* pTexture = I_Tex.Load(L"../../data/ui/main_shop_nor.png");
		btn->_pCurrentTex = pTexture;
		btn->_pStateList.push_back(pTexture);
		pTexture = I_Tex.Load(L"../../data/ui/main_shop_sel.png");
		btn->_pStateList.push_back(pTexture);
		pTexture = I_Tex.Load(L"../../data/ui/main_shop_pus.png");
		btn->_pStateList.push_back(pTexture);
		pTexture = I_Tex.Load(L"../../data/ui/main_shop_dis.png");
		btn->_pStateList.push_back(pTexture);
		btn->SetRect({ 0, 0,
			_listControl->_rtInit.w * 0.8f,
			_listControl->_rtInit.h / iNumBtn, });
		btn->SetPosition({ _listControl->_vPos.x,
							_listControl->_rtCollision.y1
							+ iBtn * (_listControl->_rtCollision.h / iNumBtn)
							+ (_listControl->_rtCollision.h / iNumBtn) / 2.0f });

		_listControl->_btnList.push_back(btn);
	}
	return true;
}
bool SceneTitle::Frame()
{
	_btnStart->Frame();
	_listControl->Frame();
	return true;
}
bool SceneTitle::Render()
{
	_pMapTitle->Render();
	_btnStart->Render();
	_listControl->Render();
	return true;
}
bool SceneTitle::Release()
{
	_pMapTitle->Release();
	_btnStart->Release();
	_listControl->Release();
	return true;
}

bool SceneTitle::IsNextScene()
{
	if (_btnStart->_currentState == UIState::UI_SELECT)
	{
		return true;
	}
	return false;
}
