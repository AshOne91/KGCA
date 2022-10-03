#pragma once
#include "Object2D.h"
#include "Component.h"

class Object2DComponent : public Object2D, public ComponentObject
{
public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;
};

