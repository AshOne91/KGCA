#pragma once
#include "Object2D.h"

class Spawner;
class Monster : public Object2D
{
public:
	int _iHearth;
	int _iAttack;

public:
	Monster* Clone(Spawner* pSpawner);

public:
	void UpdateVertexBuffer() override;
	bool Frame() override;

public:
	Monster(int iHearth, int iAttack);
	virtual ~Monster();
};

