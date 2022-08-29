#pragma once
#include "GameObject.h"

class Monster : public GameObject
{
public:
	Monster(GameApp* app, unsigned __int64 faction, float posX, float posY, float posZ, float radius);
	virtual ~Monster();

public:
	void Update(float dt) final;
};

