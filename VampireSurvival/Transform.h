#pragma once
#include "Vector.h"

class Transform
{
private:
	Vector2D _vPosition = { 0,0 };
	Vector2D _vScale = { 0,0 };

public:
	void SetPostion(Vector2D vPosition) 
	{
		_vPosition = vPosition;
	}
	Vector2D GetPosition()
	{
		return _vPosition;
	}
};
