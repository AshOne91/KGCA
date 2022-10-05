#pragma once
#include "Object2DComponent.h"
#include "TimeCounter.h"
#include <unordered_map>

class Spawner;
class Monster : public Object2DComponent
{
public:
	int _iHearth = 100.0f;
	int _iAttack = 1.0f;
	int _blinkTick = 100;
	int _blinkTickCounter = 0;
	std::vector<Vector2D> _forceList;
	TimeCounter _immuneCounter;
	TimeCounter _blinkTimer;
	bool _bImmue = false;

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

public:
	virtual void Damanged(int damanged);
	virtual void SetImmuneCounter(int counter);
	virtual bool IsImmune();
	virtual bool UpdateBlink();
};

