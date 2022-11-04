#include "Sample.h"

bool Sample::Init()
{
	_pTitle = std::make_shared<SceneTitle>();
	_pInGame = std::make_shared<SceneInGame>();
	_pTitle->Create(_pd3dDevice.Get(), _pImmediateContext.Get(), L"");
	_pInGame->Create(_pd3dDevice.Get(), _pImmediateContext.Get(), L"");
	_pTitle->Init();
	_pInGame->Init();
	_pCurrentScene = _pTitle;

	_Quadtree.Create(
		((SceneTitle*)_pCurrentScene.get())->_pMainCamera,
		((SceneTitle*)_pCurrentScene.get())->_pMap);

	//std::wstring shaderfilename = L"DefaultShape.txt";
	//m_DirLine.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), shaderfilename,
	//	L"../../data/gameHeight.png");

	////m_DirLine.m_matWorld.Scale(1000.0f, 1000.0f, 1000.0f);
	//D3DXMatrixScaling(&m_DirLine.m_matWorld, 1000.0f, 1000.0f, 1000.0f);
	return true;
}
bool Sample::Frame()
{
	//if (I_Input.GetKey(VK_F1) == KEY_PUSH)
	if (_pCurrentScene->IsNextScene())
	{
		_pCurrentScene = _pInGame;
	}
	_pCurrentScene->Frame();
	return true;
}
bool Sample::Render()
{
	if (I_Input.GetKey('V') == KEY_HOLD)
	{
		_pImmediateContext->RSSetState(DxState::g_pDefaultRSWireFrame);
	}
	_pImmediateContext->OMSetDepthStencilState(DxState::g_pDefaultDepthStencil, 0xff);
	SceneTitle* pScene = (SceneTitle*)_pCurrentScene.get();
	pScene->_pMap->SetMatrix(nullptr,
		&pScene->_pMainCamera->_matView,
		&pScene->_pMainCamera->_matProj);
	_Quadtree.Frame();
	_Quadtree.Render();
	_pCurrentScene->Render();
	return true;
}
bool Sample::Release()
{
	_pTitle->Release();
	_pInGame->Release();
	return true;
}

GAME_RUN(TSampleCollisionTest, 800, 600)