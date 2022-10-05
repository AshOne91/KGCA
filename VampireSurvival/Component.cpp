#include "Component.h"
#include "EventManager.h"
#include "Message.h"

unsigned __int64 ComponentObject::s_uiAllocIndex = 0;

ComponentObject::ComponentObject() : _uiIndex(++s_uiAllocIndex)
{
}

unsigned __int64 ComponentObject::GetIndex()
{
	return _uiIndex;
}

ComponentObject::~ComponentObject()
{
	CRelease();
}

bool ComponentObject::CInit()
{
	for (auto& component : _componentList)
	{
		component.second->CInit();
	}
	return true;
}

bool ComponentObject::CFrame()
{
	for (auto& component : _componentList)
	{
		component.second->CFrame();
	}
	return true;
}

bool ComponentObject::CRender()
{
	for (auto& component : _componentList)
	{
		component.second->CRender();
	}
	return true;
}

bool ComponentObject::CRelease()
{
	for (auto& component : _componentList)
	{
		Message msg;
		msg.eventType = EventType::ReleaseComponent;
		msg._uiSender = GetIndex();
		msg._uiReceiver = 0;
		msg._pExtraInfo = component.second;
		I_EventManager.PostNotifycation(EventType::ReleaseComponent, NotifyType::BroadCast, this, &msg);
		component.second->CRelease();
		delete component.second;
	}
	_componentList.clear();
	return true;
}

bool ComponentObject::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	for (auto& component : _componentList)
	{
		component.second->OnEvent(eventType, pSender, msg);
	}
	return true;
}

void ComponentObject::DestroyObject(unsigned __int64 uiIndex)
{
	PostNotify(EventType::DestroyObjectInComponent, NotifyType::BroadCast, this, &uiIndex);
}

void ComponentObject::PostNotify(EventType eventType, NotifyType notiType, ComponentObject* pSender, void* pExtraInfo)
{
	Message message;
	message.eventType = eventType;
	message._uiSender = GetIndex();
	message._uiReceiver = 0;
	message._pExtraInfo = pExtraInfo;
	I_EventManager.PostNotifycation(eventType, notiType, pSender, &message);
}
