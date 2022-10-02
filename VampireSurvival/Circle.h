#pragma once
#include "Collision.h"
#include "Component.h"

class CircleComponent : public Circle, public ComponentObject
{
public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;
};