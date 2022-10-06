#include "Scene.h"
#include "GameWorld.h"
void Scene::Enter()
{
	Set(I_GameWorld.GetDevice(), I_GameWorld.GetDeviceImmediateContext());
	OnEnter();
}

void Scene::Execute()
{
	OnExecute();
}

void Scene::Exit()
{
	for (auto& pair :_objectList)
	{
		I_ObjectManager.DestroyObject(pair.first);
	}
	for (auto textIndex : _textList)
	{
		I_TextManager.DestroyText(textIndex);
	}
	for (auto uiIndex : _uiList)
	{
		I_UIManager.DestroyUI(uiIndex);
	}
	_objectList.clear();
	_textList.clear();
	_uiList.clear();
	OnExit();
}

void Scene::Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmediateContext;
}
