#include "SceneTitle.h"
#
bool SceneTitle::Init()
{
	std::wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	_pMap = new MapObject;
	_pMap->Create(_pd3dDevice,
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
	_pMap->Render();
	return true;
}
bool SceneTitle::Release()
{
	_pMap->Release();
	return true;
}
