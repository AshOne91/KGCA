#include "ObjectManager.h"
#include "EventManager.h"

void ObjectManager::Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmediateContext;
}

bool ObjectManager::CInit()
{
	for (auto& pair : _objectList)
	{
		pair.second->CInit();
	}
	return true;
}

bool ObjectManager::CFrame()
{
	for (auto& pair : _objectList)
	{
		pair.second->CFrame();
	}
	return true;
}

bool ObjectManager::CRender()
{
	for (auto& pair : _objectList)
	{
		pair.second->CRender();
	}
	return true;
}

bool ObjectManager::CRelease()
{
	for (auto& pair : _objectList)
	{
		pair.second->CRelease();
	}
	return true;
}

bool ObjectManager::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	return true;
}

void ObjectManager::DestroyObject(unsigned __int64 iIndex)
{
	
}

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	CRelease();
}
