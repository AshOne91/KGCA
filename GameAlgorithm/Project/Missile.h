#pragma once
#include "GameObject.h"

class Missile : public GameObject
{
public:
	Missile(GameApp* app, unsigned __int64 faction, Vector3D pos, Vector3D size);
	virtual ~Missile();

public:
	void Update(float dt) final;

private:
	unsigned __int64 m_TargetIdx = 0;
};

