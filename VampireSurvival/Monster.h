#pragma once
#include "Object2D.h"
#include "Component.h"

class Spawner;
class Monster : public Object2D, public ComponentObject
{
public:
	int _iHearth;
	int _iAttack;

public:
	Monster* Clone(Spawner* pSpawner);

public:
	virtual void SetPosition(const Vector2D& vPos, const Vector2D& vCamera) override;
	virtual void UpdateVertexBuffer() override;
	virtual bool Frame() override;

public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;
};

