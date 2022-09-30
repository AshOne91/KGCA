#pragma once
#include "Component.h"
#include "User2D.h"

class User2DComponent : public User2D, public ComponentObject
{
public:
	virtual void UpdateVertexBuffer() override;
	virtual bool Frame() override;
	virtual bool Render() override;

public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;
};

