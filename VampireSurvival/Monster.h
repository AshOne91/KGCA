#pragma once
#include "Object2D.h"

class Monster : public Object2D
{
public:
	int _iHearth;
	int _iAttack;

public:
	Monster(int iHearth, int iAttack);
	virtual ~Monster();
};

