#pragma once
#include "Vector.h"

class InvertedAABBox2D
{
private:
	Vector2D _vTopLeft;
	Vector2D _vBottomRight;

	Vector2D _vCenter;

public:
	InvertedAABBox2D(Vector2D tl, Vector2D br) :_vTopLeft(tl), _vBottomRight(br), _vCenter((tl + br) / 2.0f) {}

	Vector2D TopLeft() const { return _vTopLeft; }
	Vector2D BottomRight() const { return _vBottomRight; }

	float Top() const { return _vTopLeft.y; }
	float Left() const { return _vTopLeft.x; }
	float Bottom() const { return _vBottomRight.y; }
	float Right() const { return _vBottomRight.x; }
	Vector2D Center() const { return _vCenter; }

	void Render(bool RenderCenter = false) const
	{
		/*gdi->Line((int)Left(), (int)Top(), (int)Right(), (int)Top());
		gdi->Line((int)Left(), (int)Bottom(), (int)Right(), (int)Bottom());
		gdi->Line((int)Left(), (int)Top(), (int)Left(), (int)Bottom());
		gdi->Line((int)Right(), (int)Top(), (int)Right(), (int)Bottom());*/

		if (RenderCenter)
		{
			//gdi->Circle(_vCenter, 5);
		}
	}

	bool isOverlappedWith(const InvertedAABBox2D& other) const
	{
		return !((other.Top() > this->Bottom()) ||
			(other.Bottom() < this->Top()) ||
			(other.Left() > this->Right()) ||
			(other.Right() < this->Left()));
	}
};

