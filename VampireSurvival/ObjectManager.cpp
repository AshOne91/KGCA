#include "ObjectManager.h"
#include "EventManager.h"
#include "GameWorld.h"

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
	_fRenderCheckRadious = float(dfSCREEN_WIDTH * dfSCREEN_WIDTH) + float(dfSCREEN_HEIGHT * dfSCREEN_HEIGHT);
	_fRenderCheckRadious = sqrtf(_fRenderCheckRadious) * 0.5f;
	return true;
}

bool ObjectManager::CFrame()
{
	if (_destoryObjectList[_destoryIndex].size() > 0)
	{
		int preIndex = _destoryIndex;
		_destoryIndex = (_destoryIndex + 1) % 2;
		for (auto& index : _destoryObjectList[preIndex])
		{
			DestroyObject(index);
		}
		_destoryObjectList[preIndex].clear();
	}

	for (auto& pair : _objectList)
	{
		pair.second->CFrame();
		Circle circle;
		circle.cx = pair.second->_transform.GetPosition().x;
		circle.cy = pair.second->_transform.GetPosition().y;
		circle.fRadius = pair.second->_transform.GetRadious();
		Circle checkCircle;
		checkCircle.cx = I_GameWorld.GetCameraPos().x;
		checkCircle.cy = I_GameWorld.GetCameraPos().y;
		checkCircle.fRadius = _fRenderCheckRadious;
		if (Collision::CircleToCircle(circle, checkCircle))
		{
			_renderCheck.push_back(pair.second);
		}
	}
	return true;
}

bool ObjectManager::CRender()
{
	for (auto& obj : _renderCheck)
	{
		obj->CRender();
	}
	_renderCheck.clear();
	return true;
}

bool ObjectManager::CRelease()
{
	for (auto& pair : _objectList)
	{
		pair.second->CRelease();
		delete pair.second;
	}
	_objectList.clear();
	return true;
}

bool ObjectManager::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	if (eventType == EventType::CreateObjectInComponent)
	{
		BaseObject* pObj = static_cast<BaseObject*>(msg->_pExtraInfo);
		ComponentObject* pComponent = dynamic_cast<ComponentObject*>(pObj);
		_objectList.insert({ pComponent->GetIndex(), pComponent });
		pComponent->CInit();

		Message msg;
		msg.eventType = EventType::CreateObject;
		msg._uiSender = GetIndex();
		msg._uiReceiver = 0;
		msg._pExtraInfo = pComponent;
		I_EventManager.PostNotifycation(EventType::CreateObject, NotifyType::BroadCast, this, &msg);
	}

	if (eventType == EventType::DestroyObjectInComponent)
	{
		unsigned __int64 index = *(static_cast<unsigned __int64*>(msg->_pExtraInfo));
		_destoryObjectList[_destoryIndex].push_back(index);
		//DestroyObject(index);
	}
	return true;
}

void ObjectManager::DestroyObject(unsigned __int64 iIndex)
{
	auto iter = _objectList.find(iIndex);
	if (iter == _objectList.end())
	{
		//누가 지운거다.(두번 호출 될 수 있음)
		return;
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
