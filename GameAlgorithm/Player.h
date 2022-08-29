#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player(GameApp* app, Vector3D pos, Vector3D size);
	virtual ~Player();

public:
	void Update(float dt) final;
	void FireMissile();
};

