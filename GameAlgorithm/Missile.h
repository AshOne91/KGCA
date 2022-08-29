#pragma once
#include "GameObject.h"

class Missile : public GameObject
{
public:
	Missile(GameApp* app, unsigned __int64 faction, float posX, float posY, float posZ, float radius);
	virtual ~Missile();

public:
	void Update(float dt) final;

private:
	unsigned __int64 m_TargetIdx = 0;
};

