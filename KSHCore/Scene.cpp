#include "Scene.h"

bool Scene::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring shadername)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmediateContext;
	return true;
}

bool Scene::Init()
{
	return true;
}

bool Scene::Frame()
{
	return true;
}

bool Scene::Render()
{
	return true;
}

bool Scene::Release()
{
	return true;
}
