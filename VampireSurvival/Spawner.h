#pragma once
#include "Object2D.h"
#include "Component.h"
#include "TimeCounter.h"

class Monster;
class Spawner : public Object2D, public ComponentObject
{
private:
	TimeCounter _timerCounter;
	Monster* _pMonsterPrototype = nullptr;

public:
	virtual bool Init() final;
	virtual bool Frame() final;
	virtual bool Render() final;
	virtual bool Release() final;

public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;

public:
	void SetMonsterPrototype(Monster* pMonster);
	Monster* SpawnMonster();
};

