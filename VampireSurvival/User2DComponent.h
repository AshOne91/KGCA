#pragma once
#include "Component.h"
#include "Object2DComponent.h"
#include "Vehicle.h"
#include "TimeCounter.h"
#include <vector>

class Skill;
class User2DComponent : public Object2DComponent
{
public:
	TimeCounter _explosionCounter;

public:
	virtual void UpdateVertexBuffer() override;
	virtual bool Frame() override;
	virtual void SetPosition(const Vector2D& vPos, const Vector2D& vCamera) override;
	virtual bool Render() override;

public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;
};

