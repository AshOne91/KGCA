#include "Circle.h"
#include "EventManager.h"

bool CircleComponent::CInit()
{
	I_EventManager.AddListener(EventType::CollisionIn, GetParentPtr());
	I_EventManager.AddListener(EventType::CollisionOut, GetParentPtr());
	return true;
}

bool CircleComponent::CFrame()
{
	return true;
}

bool CircleComponent::CRender()
{
	return true;
}

bool CircleComponent::CRelease()
{
	ComponentObject::CRelease();
	return true;
}

bool CircleComponent::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	return true;
}
