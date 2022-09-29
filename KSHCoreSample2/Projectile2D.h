#pragma once
#include "Effect2D.h"

struct Projectile2D : public Effect2D
{
public:
	virtual bool Update() override;
	Projectile2D();
};

