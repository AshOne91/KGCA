#pragma once
#include "GameObject.h"

class Monster : public GameObject
{
public:
	Monster(GameApp* app, unsigned __int64 faction, Vector3D pos, Vector3D size);
	virtual ~Monster();

public:
	void Update(float dt) final;
};

