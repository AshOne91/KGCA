#pragma once
#include "Object2D.h"
enum class MapCollisionType
{
	LeftUp = 0,
	UP = 1,
	RightUp= 2,
	Right = 3,
	RightDown = 4,
	Down = 5,
	LeftDown = 6,
	Left = 7
};

class MapObject : public Object2D
{
public:
	bool   Frame() override;
	void  UpdateVertexBuffer() override;
};

