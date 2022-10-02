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
	_objectList.clear();
	return true;
}

bool ObjectManager::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	return true;
}

void ObjectManager::DestroyObject(unsigned __int64 iIndex)
{
	auto iter = _objectList.find(iIndex);
	if (iter == _objectList.end())
	{
		int* p = 0;
		*p = 1;
	}
	iter->second->CRelease();
	Message msg;
	msg.eventType = EventType::DestroyObject;
	msg._uiSender = GetIndex();
	msg._uiReceiver = 0;
	msg._pExtraInfo = iter->second;
	I_EventManager.PostNotifycation(EventType::DestroyObject, NotifyType::BroadCast, this, &msg);
	delete iter->second;
	_objectList.erase(iIndex);
}

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	CRelease();
}
