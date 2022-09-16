#pragma once
#include "Vector.h"

class Wall2D
{
protected:
	Vector2D _vA, _vB, _vN;

	void CalculateNormal()
	{

		Vector2D temp(_vB - _vA);
		temp.Normalize();

		_vN.x = -temp.y;
		_vN.y = temp.x;
	}

public:
	Wall2D() {}

	Wall2D(Vector2D A, Vector2D B) :_vA(A), _vB(B)
	{
		CalculateNormal();
	}

	Wall2D(Vector2D A, Vector2D B, Vector2D N) :_vA(A), _vB(B), _vN(N)
	{}

	virtual void Render(bool RenderNormals = false) const
	{
		//gdi->Line(_vA, _vB);

		if (RenderNormals)
		{
			int MidX = (int)((_vA.x + _vB.x) / 2);
			int MidY = (int)((_vA.y + _vB.y) / 2);

			// 5¸¦ ¿Ö°öÇÏÁö?
			//gdi->Line(MidX, MidY, (int)(MidX + (_vN.x * 5)), (int)(MidY + (_vN.y * 5)));
		}
	}

	Vector2D From()const { return _vA; }
	void SetFrom(Vector2D v) { _vA = v; CalculateNormal(); }

	Vector2D To() const { return _vB; }
	void SetTo(Vector2D v) { _vB = v; CalculateNormal(); }

	Vector2D Normal() const { return _vN; }
	void SetNormal(Vector2D n) { _vN = n; }

	Vector2D Center() const { return (_vA + _vB) / 2.0f; }
};

