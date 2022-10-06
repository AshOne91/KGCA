#pragma once
#include "Interface.h"
#include "Component.h"

class UIHpBar : public Interface, public ComponentObject
{
public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;
};

