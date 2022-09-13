#pragma once

#include <vector>

#include "Vector.h"
#include "C2DMatrix.h"

std::vector<Vector2D> WorldTransform(std::vector<Vector2D>& points,
	const Vector2D& pos,
	const Vector2D& forward,
	const Vector2D& side,
	const Vector2D& scale)
{
	std::vector<Vector2D> TranVector2Ds = points;
	C2DMatrix matTransform;

	if ((scale.x != 1.0f) || (scale.y != 1.0f))
	{
		matTransform.Scale(scale.x, scale.y);
	}

	matTransform.Rotate(forward, side);

	matTransform.Translate(pos.x, pos.y);

	matTransform.TransformVector2Ds(TranVector2Ds);

	return TranVector2Ds;
}

std::vector<Vector2D> WorldTransform(std::vector<Vector2D>& points,
	const Vector2D& pos,
	const Vector2D& forward,
	const Vector2D& side)
{
	std::vector<Vector2D> TranVector2Ds = points;
	C2DMatrix matTransform;

	matTransform.Rotate(forward, side);

	matTransform.Translate(pos.x, pos.y);

	matTransform.TransformVector2Ds(TranVector2Ds);

	return TranVector2Ds;
}

Vector2D PointToWorldSpace(const Vector2D& point,
	const Vector2D& AgentHeading,
	const Vector2D& AgentSide,
	const Vector2D& AgentPosition)
{
	//make a copy of the point
	Vector2D TransPoint = point;

	//create a transformation matrix
	C2DMatrix matTransform;

	//rotate
	matTransform.Rotate(AgentHeading, AgentSide);

	//and translate
	matTransform.Translate(AgentPosition.x, AgentPosition.y);

	//now transform the vertices
	matTransform.TransformVector2Ds(TransPoint);

	return TransPoint;
}

Vector2D VectorToWorldSpace(const Vector2D& vec,
	const Vector2D& AgentHeading,
	const Vector2D& AgentSide)
{
	//make a copy of the point
	Vector2D TransVec = vec;

	//create a transformation matrix
	C2DMatrix matTransform;

	//rotate
	matTransform.Rotate(AgentHeading, AgentSide);

	//now transform the vertices
	matTransform.TransformVector2Ds(TransVec);

	return TransVec;
}

Vector2D PointToLocalSpace(const Vector2D& point,
	Vector2D& AgentHeading,
	Vector2D& AgentSide,
	Vector2D& AgentPosition)
{

	//make a copy of the point
	Vector2D TransPoint = point;

	//create a transformation matrix
	C2DMatrix matTransform;

	float Tx = -AgentPosition.Dot(AgentHeading);
	float Ty = -AgentPosition.Dot(AgentSide);

	//create the transformation matrix
	matTransform._11(AgentHeading.x); matTransform._12(AgentSide.x);
	matTransform._21(AgentHeading.y); matTransform._22(AgentSide.y);
	matTransform._31(Tx);           matTransform._32(Ty);

	//now transform the vertices
	matTransform.TransformVector2Ds(TransPoint);

	return TransPoint;
}

Vector2D PointToLocalSpace(const Vector2D& point,
	Vector2D& AgentHeading,
	Vector2D& AgentSide,
	Vector2D& AgentPosition)
{

	//make a copy of the point
	Vector2D TransPoint = point;

	//create a transformation matrix
	C2DMatrix matTransform;

	double Tx = -AgentPosition.Dot(AgentHeading);
	double Ty = -AgentPosition.Dot(AgentSide);

	//create the transformation matrix
	matTransform._11(AgentHeading.x); matTransform._12(AgentSide.x);
	matTransform._21(AgentHeading.y); matTransform._22(AgentSide.y);
	matTransform._31(Tx);           matTransform._32(Ty);

	//now transform the vertices
	matTransform.TransformVector2Ds(TransPoint);

	return TransPoint;
}

Vector2D VectorToLocalSpace(const Vector2D& vec,
	const Vector2D& AgentHeading,
	const Vector2D& AgentSide)
{

	//make a copy of the point
	Vector2D TransPoint = vec;

	//create a transformation matrix
	C2DMatrix matTransform;

	//create the transformation matrix
	matTransform._11(AgentHeading.x); matTransform._12(AgentSide.x);
	matTransform._21(AgentHeading.y); matTransform._22(AgentSide.y);

	//now transform the vertices
	matTransform.TransformVector2Ds(TransPoint);

	return TransPoint;
}

void Vec2DRotateAroundOrigin(Vector2D& v, float ang)
{
	//create a transformation matrix
	C2DMatrix mat;

	//rotate
	mat.Rotate(ang);

	//now transform the object's vertices
	mat.TransformVector2Ds(v);
}

std::vector<Vector2D> CreateWhiskers(unsigned int  NumWhiskers,
	float        WhiskerLength,
	float        fov,
	Vector2D      facing,
	Vector2D      origin)
{
	//this is the magnitude of the angle separating each whisker
	double SectorSize = fov / (float)(NumWhiskers - 1);

	std::vector<Vector2D> whiskers;
	Vector2D temp;
	float angle = -fov * 0.5;

	for (unsigned int w = 0; w < NumWhiskers; ++w)
	{
		//create the whisker extending outwards at this angle
		temp = facing;
		Vec2DRotateAroundOrigin(temp, angle);
		whiskers.push_back((origin + WhiskerLength * temp);

		angle += SectorSize;
	}

	return whiskers;
}