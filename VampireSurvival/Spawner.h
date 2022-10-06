#pragma once
#include "Object2D.h"
#include "Component.h"
#include "TimeCounter.h"
#include "Monster.h"
#include <Vector.h>

class Monster;
class Spawner : public Object2D, public ComponentObject
{
private:
	TimeCounter _timerCounter;

public:
	virtual bool Init() final;
	virtual bool Frame() final;
	virtual bool Render() final;

public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;

public:
	void EnableSpawner();
	void DisableSpawner();
};

