#include "Object2DComponent.h"

bool Object2DComponent::CInit()
{
	return Object2D::Init();
}

bool Object2DComponent::CFrame()
{
	return Object2D::Frame();
}

bool Object2DComponent::CRender()
{
	return Object2D::Render();
}

bool Object2DComponent::CRelease()
{
	return Object2D::Release();
}

bool Object2DComponent::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	return true;
}
