#include "SceneTitle.h"
#include "Input.h"

bool SceneTitle::Init()
{
	I_Sprite.Load(L"SpriteInfo.txt");
	I_Sprite.Load(L"ui.txt");
	std::wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	_pBG = new BaseObject;
	_pBG->Create(_pd3dDevice, _pImmediateContext, shaderfilename, L"../../data/gameHeight.png");

	_pBoxObj = new ShapeBox;
	_pBoxObj->Create(_pd3dDevice, _pImmediateContext, L"DefaultObject.txt", L"../../data/gameHeight.png");

	_pMainCamera = new Camera;
	_pMainCamera->CreateViewMatrix(Vector3D(0, 0, -10), Vector3D(0, 0, 0), Vector3D(0, 1, 0));
	_pMainCamera->CreateProjMatrix(1.0f, 100.0f, PI * 0.5f,
		(float)g_rtClient.right / (float)g_rtClient.bottom);

	return true;
}
bool SceneTitle::Frame()
{
	_pMainCamera->Frame();
	_pBoxObj->Frame();
	return true;
}
bool SceneTitle::Render()
{
	_pBoxObj->SetMatrix(nullptr, &_pMainCamera->_matView, &_pMainCamera->_matProj);
	_pBoxObj->Render();
	//_pBG->Render();
	return true;
}
bool SceneTitle::Release()
{
	_pBG->Release();
	_pBoxObj->Release();
	delete _pBoxObj;
	delete _pBG;
	return true;
}

bool SceneTitle::IsNextScene()
{
	return false;
}
