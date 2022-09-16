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

	D3D11_VIEWPORT vp;
	vp.Width = 400;
	vp.Height = 300;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	_pImmediateContext->RSSetViewports(1, &vp);
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
	D3D11_VIEWPORT vp;
	vp.Width = 800;
	vp.Height = 600;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	_pImmediateContext->RSSetViewports(1, &vp);
	_pCurrentScene->Render();

	vp.Width = 100;
	vp.Height = 100;
	vp.TopLeftX = 0;
	vp.TopLeftY = 500;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	_pImmediateContext->RSSetViewports(1, &vp);
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