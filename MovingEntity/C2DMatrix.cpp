#include "C2DMatrix.h"

void C2DMatrix::MatrixMultiply(const Matrix& mIn)
{
	C2DMatrix::Matrix mat_temp;

	//first row
	mat_temp._11 = (_Matrix._11 * mIn._11) + (_Matrix._12 * mIn._21) + (_Matrix._13 * mIn._31);
	mat_temp._12 = (_Matrix._11 * mIn._12) + (_Matrix._12 * mIn._22) + (_Matrix._13 * mIn._32);
	mat_temp._13 = (_Matrix._11 * mIn._13) + (_Matrix._12 * mIn._23) + (_Matrix._13 * mIn._33);

	//second
	mat_temp._21 = (_Matrix._21 * mIn._11) + (_Matrix._22 * mIn._21) + (_Matrix._23 * mIn._31);
	mat_temp._22 = (_Matrix._21 * mIn._12) + (_Matrix._22 * mIn._22) + (_Matrix._23 * mIn._32);
	mat_temp._23 = (_Matrix._21 * mIn._13) + (_Matrix._22 * mIn._23) + (_Matrix._23 * mIn._33);

	//third
	mat_temp._31 = (_Matrix._31 * mIn._11) + (_Matrix._32 * mIn._21) + (_Matrix._33 * mIn._31);
	mat_temp._32 = (_Matrix._31 * mIn._12) + (_Matrix._32 * mIn._22) + (_Matrix._33 * mIn._32);
	mat_temp._33 = (_Matrix._31 * mIn._13) + (_Matrix._32 * mIn._23) + (_Matrix._33 * mIn._33);

	_Matrix = mat_temp;
}

void C2DMatrix::Identity()
{
	_Matrix._11 = 1; _Matrix._12 = 0; _Matrix._13 = 0;

	_Matrix._21 = 0; _Matrix._22 = 1; _Matrix._23 = 0;

	_Matrix._31 = 0; _Matrix._32 = 0; _Matrix._33 = 1;
}

void C2DMatrix::Translate(float x, float y)
{
	Matrix mat;

	mat._11 = 1; mat._12 = 0; mat._13 = 0;

	mat._21 = 0; mat._22 = 1; mat._23 = 0;

	mat._31 = x;    mat._32 = y;    mat._33 = 1;

	//and multiply
	MatrixMultiply(mat);
}

void C2DMatrix::Scale(float xScale, float yScale)
{
	C2DMatrix::Matrix mat;

	mat._11 = xScale; mat._12 = 0; mat._13 = 0;

	mat._21 = 0; mat._22 = yScale; mat._23 = 0;

	mat._31 = 0; mat._32 = 0; mat._33 = 1;

	//and multiply
	MatrixMultiply(mat);
}

void C2DMatrix::Rotate(float rotation)
{
	C2DMatrix::Matrix mat;

	double Sin = sin(rotation);
	double Cos = cos(rotation);

	mat._11 = Cos;  mat._12 = Sin; mat._13 = 0;

	mat._21 = -Sin; mat._22 = Cos; mat._23 = 0;

	mat._31 = 0; mat._32 = 0; mat._33 = 1;

	//and multiply
	MatrixMultiply(mat);
}

void C2DMatrix::Rotate(const Vector2D& fwd, const Vector2D& side)
{
	C2DMatrix::Matrix mat;

	mat._11 = fwd.x;  mat._12 = fwd.y; mat._13 = 0;

	mat._21 = side.x; mat._22 = side.y; mat._23 = 0;

	mat._31 = 0; mat._32 = 0; mat._33 = 1;

	//and multiply
	MatrixMultiply(mat);
}

void C2DMatrix::TransformVector2Ds(std::vector<Vector2D>& vPoints)
{
	for (unsigned int i = 0; i < vPoints.size(); ++i)
	{
		float tempX = (_Matrix._11 * vPoints[i].x) + (_Matrix._21 * vPoints[i].y) + (_Matrix._31);

		float tempY = (_Matrix._12 * vPoints[i].x) + (_Matrix._22 * vPoints[i].y) + (_Matrix._32);

		vPoints[i].x = tempX;

		vPoints[i].y = tempY;

	}
}

void C2DMatrix::TransformVector2Ds(Vector2D& vPoint)
{
	float tempX = (_Matrix._11 * vPoint.x) + (_Matrix._21 * vPoint.y) + (_Matrix._31);

	float tempY = (_Matrix._12 * vPoint.x) + (_Matrix._22 * vPoint.y) + (_Matrix._32);

	vPoint.x = tempX;

	vPoint.y = tempY;
}
