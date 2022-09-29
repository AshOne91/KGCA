#include "SceneTitle.h"

bool SceneTitle::Init()
{
	I_Sprite.Load(L"SpriteInfo.txt");
	I_Sprite.Load(L"ui.txt");
	std::wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	_pMapTitle = new BaseObject;
	_pMapTitle->Create(_pd3dDevice, _pImmediateContext, shaderfilename, L"../../data/gameHeight.png");

	_Dlg = new Dialog;
	_Dlg->Create(_pd3dDevice, _pImmediateContext, shaderfilename, L"../../data/ui/popup_normal.png");
	_Dlg->SetAttribute({ 300, 200 }, { 0, 0, 400.0f, 300.0f });
	/////////////// position ///////
	//       left          right
	// u -> 0~0.1f  ~     0.9f~1.0f
	//        top          bottom
	// v -> 0~0.1f  ~     0.9f~1.0f
	/////////////// uv ///////
	//       left          right
	// u -> 0~0.2f  ~     0.8f~1.0f
	//        top          bottom
	// v -> 0~0.33f  ~     0.67f~1.0f
	_Dlg->SetDrawList(0.1f, 0.1f, 0.1f, 0.1f, 0.2f, 0.2f, 0.33f, 0.33f);

	_btnStart = new Button;
	_btnStart->Create(_pd3dDevice, _pImmediateContext, shaderfilename, L"../../data/ui/main_start_nor.png");
	std::vector<W_STR> stateList;
	stateList.push_back(L"../../data/ui/main_start_nor.png");
	stateList.push_back(L"../../data/ui/main_start_sel.png");
	stateList.push_back(L"../../data/ui/main_start_pus.png");
	stateList.push_back(L"../../data/ui/main_start_dis.png");
	_btnStart->SetAttribute({ 400.0f, 300.0f }, { 0, 0, 100, 60 }, stateList);

	_btnStart2 = new Button;
	_btnStart2->Create(_pd3dDevice, _pImmediateContext, shaderfilename, L"../../data/ui/main_start_nor.png");
	_btnStart2->SetAttribute({ 400.0f, 500.0f }, { 0,0, 100, 60 },
		I_Sprite.GetPtr(L"NormalButton3"));

	_listControl = new ListControl;
	_listControl->Create(_pd3dDevice, _pImmediateContext, shaderfilename, L"../../data/ui/RAINBOW.png");
	_listControl->SetAttribute({ 300 - 100, 300 - 100 }, { 0, 0,	100.0f, 250.0f });
	UINT iNumBtn = 10;
	for (int iBtn = 0; iBtn < iNumBtn; ++iBtn)
	{
		Interface* btn = new Button;
		btn->Create(_pd3dDevice, _pImmediateContext, shaderfilename, L"../../data/ui/main_plus_dis.png");
		Vector2D vPos = { _listControl->_vPos.x,
			  _listControl->_rtCollision.y1 + iBtn * (_listControl->_rtCollision.h / iNumBtn) + (_listControl->_rtCollision.h / iNumBtn) / 2.0f };
		Rect rt = { 0, 0,	_listControl->_rtInit.w, _listControl->_rtInit.h / iNumBtn };
		btn->SetAttribute(vPos, rt, stateList);
		_listControl->AddChild(btn);
	}

	_Dlg->AddChild(_btnStart);
	_Dlg->AddChild(_listControl);

	_FadeObject = new Interface;
	_FadeObject->Create(_pd3dDevice, _pImmediateContext, shaderfilename, L"../../data/black.png");
	return true;
}
bool SceneTitle::Frame()
{
	_btnStart2->Frame();

	_btnStart->Frame();
	_listControl->Frame();
	Vector2D pos = _Dlg->_vPos;
	pos.x = pos.x + g_fSecondPerFrame * 10.0f;
	_Dlg->SetPosition(pos);
	_Dlg->Frame();

	static float fAlpha = 0.0f;
	_FadeObject->FadeInOut(cosf(g_fGameTimer) * 0.5f + 0.5f);
	_FadeObject->Frame();
	return true;
}
bool SceneTitle::Render()
{
	_pMapTitle->Render();
	_btnStart2->Render();
	_btnStart->Render();
	_Dlg->Render();

	//_FadeObject->Render();
	return true;
}
bool SceneTitle::Release()
{
	_pMapTitle->Release();
	_btnStart->Release();
	_btnStart2->Release();
	_listControl->Release();
	_Dlg->Release();

	_FadeObject->Release();
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
