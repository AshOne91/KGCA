#pragma once
#include "Vector.h"

enum class CollisionType : int
{
	OUT = 0,
	IN,
	OVERLAP
};

struct Circle
{
public:
	Vector2D center;
	float radius;
};

struct Sphere
{
public:
	Vector3D center;
	float radius;
};

struct Rect
{
	float x1;
	float x1;
	float w;
	float h;
};

struct Box2D : Rect
{
	Vector2D center;
	float x2;
	float y2;
};

struct Box
{
	Vector3D min;
	Vector3D size;
};

struct Box3D
{
	Vector3D center;
	Vector3D max;
};

