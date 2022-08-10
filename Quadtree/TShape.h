#pragma once
#include <map>
struct RECT
{
	float left;
	float top;
	float right;
	float bottom;
};
struct TVector2D
{
	float x;
	float y;
};
struct TRect : public RECT
{
public:
	TRect() {};
	TRect(float l, float t, float r, float b) 
	{
		left = l;
		top = t;
		right = r;
		bottom = b;
	}
};
class TShape
{
};

