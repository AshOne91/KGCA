#pragma once
#include "Std.h"

class C2DMatrix
{
private:

	struct Matrix
	{
		float _11, _12, _13;
		float _21, _22, _23;
		float _31, _32, _33;

		Matrix()
		{
			_11 = 0.0f; _12 = 0.0f; _13 = 0.0f;
			_21 = 0.0f; _22 = 0.0f; _23 = 0.0f;
			_31 = 0.0f; _32 = 0.0f; _33 = 0.0f;
		}
	};

	Matrix _Matrix;

	void MatrixMultiply(const Matrix& mIn);

public:
	C2DMatrix()
	{
		Identity();
	}

	void Identity();
	void Translate(float x, float y);
	void Scale(float xScale, float yScale);
	void Rotate(float rotation);
	void Rotate(const Vector2D& fwd, const Vector2D& side);
	void TransformVector2Ds(std::vector<Vector2D>& vPoints);
	void TransformVector2Ds(Vector2D& vPoint);

	void _11(float val) { _Matrix._11 = val; }
	void _12(float val) { _Matrix._12 = val; }
	void _13(float val) { _Matrix._13 = val; }

	void _21(float val) { _Matrix._21 = val; }
	void _22(float val) { _Matrix._22 = val; }
	void _23(float val) { _Matrix._23 = val; }

	void _31(float val) { _Matrix._31 = val; }
	void _32(float val) { _Matrix._32 = val; }
	void _33(float val) { _Matrix._33 = val; }
};