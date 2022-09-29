#pragma once
#include "Object2D.h"

class Npc2D : public Object2D
{
public:
	bool  Frame() override;
	Npc2D()
	{
		_fSpeed = 300.0f;
	}
};

