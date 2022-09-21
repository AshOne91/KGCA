#pragma once
#include "Object2D.h"
class User2D : public Object2D
{
public:
	bool  Frame() override;
	User2D()
	{
		_fSpeed = 400.0f;
	}
};

