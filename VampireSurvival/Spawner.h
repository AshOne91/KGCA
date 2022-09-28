#pragma once
#include "Object2D.h"
#include "TimeCounter.h"

class Monster;
class Spawner : public Object2D
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
	void SetMonsterPrototype(Monster* pMonster);
	Monster* SpawnMonster();
};

