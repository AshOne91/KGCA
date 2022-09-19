#include "SceneTitle.h"

bool SceneTitle::Init()
{
	std::wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	_pMapTitle = new BaseObject;
	_pMapTitle->Create(_pd3dDevice,
		_pImmediateContext,
		shaderfilename,
		L"../../data/kgcabk.bmp");
	return true;
}
bool SceneTitle::Frame()
{
	return true;
}
bool SceneTitle::Render()
{
	_pMapTitle->Render();
	return true;
}
bool SceneTitle::Release()
{
	_pMapTitle->Release();
	return true;
}
