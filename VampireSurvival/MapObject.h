#pragma once
#include "Object2D.h"

enum class MapRotateType
{
	Up = 0,
	Right,
	Down,
	Left
};

class Spawner;
class Monster;
class MapObject : public Object2D
{
private:
	Spawner* _pSpawner = nullptr;

public:
	void SetMonsterPrototype(Monster* pMonster);
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	virtual void UpdateVertexBuffer() override;
};

