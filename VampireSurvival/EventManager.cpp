#include "EventManager.h"
#include "Message.h"
#include <utility>

void EventManager::Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmediateContext;
}

bool EventManager::CInit()
{
	return true;
}

bool EventManager::CFrame()
{
	return true;
}

bool EventManager::CRender()
{
	return true;
}

bool EventManager::CRelease()
{
	_ListenerList.clear();
	return true;
}

bool EventManager::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	return true;
}

void EventManager::AddListener(EventType eventType, ComponentObject* pComponent)
{
	auto iter = _ListenerList.find(eventType);
	if (iter == _ListenerList.end())
	{
		_ListenerList.insert({ eventType, std::unordered_map<unsigned __int64, ComponentObject*>() });
		_ListenerList[eventType].insert({ pComponent->GetIndex(), pComponent});
		return;
	}

	auto inIter = iter->second.find(pComponent->GetIndex());
	if (inIter == iter->second.end())
	{
		iter->second.insert({ pComponent->GetIndex(), pComponent });
	}
}

void EventManager::PostNotifycation(EventType eventType, NotifyType notifyType, ComponentObject* pSender, Message* message)
{
	auto iter = _ListenerList.find(eventType);
	if (iter == _ListenerList.end())
	{
		return;
	}

	if (notifyType == NotifyType::Mono)
	{
		auto pReciver = iter->second.find(message->_uiReceiver);
		if (pReciver == iter->second.end())
		{
			return;
		}

		pReciver->second->OnEvent(eventType, pSender, message);
		return;
	}

	if (notifyType == NotifyType::BroadCast)
	{
		for (auto& pair : iter->second)
		{
			pair.second->OnEvent(eventType, pSender, message);
		}
	}
}

void EventManager::RemoveEvent(EventType eventType)
{
	_ListenerList.erase(eventType);
}

void EventManager::RemoveComponentObject(ComponentObject* pComponent)
{
	for (auto& pair : _ListenerList)
	{
		auto iter = pair.second.find(pComponent->GetIndex());
		if (iter == pair.second.end())
		{
			continue;
		}
		pair.second.erase(pComponent->GetIndex());
	}
}

EventManager::EventManager()
{

}

EventManager::~EventManager()
{
	CRelease();
}
