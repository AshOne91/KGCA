#pragma once
#include "BaseObject.h"

class MapObject : public BaseObject
{
	Vector2D _vUserPos;
public:
	bool Frame() override;
};

