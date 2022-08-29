#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player(GameApp* app, float posX, float posY, float posZ, float radius);
	virtual ~Player();

public:
	void Update(float dt) final;
	void FireMissile();
};

