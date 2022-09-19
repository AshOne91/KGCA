#include "Sample.h"

bool Sample::Init()
{
	_pTitle = new SceneTitle;
	_pInGame = new SceneInGame;
	_pTitle->Create(_pd3dDevice, _pImmediateContext, L"");
	_pInGame->Create(_pd3dDevice, _pImmediateContext, L"");
	_pTitle->Init();
	_pInGame->Init();
	_pCurrentScene = _pTitle;
	return true;
}

bool Sample::Frame()
{
	if (I_Input.GetKey(VK_F1) == KEY_PUSH)
	{
		_pCurrentScene = _pInGame;
	}
	_pCurrentScene->Frame();
	return true;
}

bool Sample::Render()
{
	_pImmediateContext->RSSetState(DxState::g_pDefaultRSWireFrame);
	_pCurrentScene->Render();
	return true;
}

bool Sample::Release()
{
	_pTitle->Release();
	_pInGame->Release();

	delete _pTitle;
	delete _pInGame;
	return true;
}

GAME_RUN(KSHCoreSample, 800, 600)