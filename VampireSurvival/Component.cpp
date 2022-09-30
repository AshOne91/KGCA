#include "Component.h"

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
		component.second->CRelease();
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
