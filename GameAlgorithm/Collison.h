#pragma once
#include "Vector.h"

class GameObject;
enum class CollisionType : int
{
	OUT = 0,
	IN,
	OVERLAP
};

struct Collision
{
	CollisionType type = CollisionType::OUT;
	GameObject* collisionObject = nullptr;
};

template <typename T>
struct Collider abstract
{
public:
	virtual bool operator == (const T& dest) = 0;
	virtual CollisionType CheckCollision(const T& a, const T& b) = 0;
};

struct Rect
{
	float x1;
	float y1;
	float w;
	float h;
};

struct Box2D : Rect, Collider<Box2D>
{
public:
	Vector2D center;
	float x2;
	float y2;

public:
	Box2D() {}
	Box2D(float x, float y, float z, float w)
	{
		Set(x, y, z, w);
	}
	void Set(float x, float y, float z, float w)
	{
		this->x1 = x;
		this->y1 = y;
		this->w = z;
		this->h = w;
		this->x2 = x + w;
		this->y2 = y + h;
		center.x = (x + x2) / 2.0f;
		center.y = (y + y2) / 2.0f;
	}

public:
	bool operator == (const Box2D& dest);
	CollisionType CheckCollision(const Box2D& a, const Box2D& b);
};

struct Box
{
	Vector3D min;
	Vector3D size;
};

struct Box3D : Box, Collider<Box3D>
{
public:
	Vector3D center;
	Vector3D max;

public:
	Box3D() {};
	Box3D(const Vector3D& pos, const Vector3D& size)
	{
		Set(pos, size);
	}
	void Set(const Vector3D& pos, const Vector3D& size)
	{
		this->min = pos;
		this->size = size;
		this->max = min + size;
		center = (min + max) / 2.0f;
	}

public:
	bool operator == (const Box3D& dest);
	CollisionType CheckCollision(const Box3D& a, const Box3D& b);
};

struct Circle : Collider<Circle>
{
public:
	Vector2D center;
	float radius;

public:
	Circle() {};
	Circle(const Vector2D& center, float radius)
	{
		Set(center, radius);
	}
	Circle(const Box2D& box2D)
	{
		Set(box2D);
	}
	void Set(const Vector2D& center, float radius)
	{
		this->center = center;
		this->radius = radius;
	}
	void Set(const Box2D& box2D)
	{
		Vector2D center;
		center.x = (box2D.x1 + box2D.x2) / 2.0f;
		center.y = (box2D.y1 + box2D.y2) / 2.0f;
		float radius = sqrtf(box2D.w * box2D.w + box2D.h * box2D.h) / 2.0f;
		Set(center, radius);
	}
public:
	bool operator == (const Circle& dest);
	CollisionType CheckCollision(const Circle& a, const Circle& b);
};

struct Sphere : Collider<Sphere>
{
public:
	Vector3D center;
	float radius;

public:
	Sphere() {};
	Sphere(const Vector3D& center, float radius)
	{
		Set(center, radius);
	}
	Sphere(const Box3D& box3D)
	{
		Set(box3D);
	}
	void Set(const Box3D& box3D)
	{
		Vector3D center = box3D.center;
		Vector3D temp = box3D.size;
		float radius = (temp * 0.5f).Length();
		Set(center, radius);
	}
	void Set(const Vector3D& center, float radius)
	{
		this->center = center;
		this->radius = radius;
	}

public:
	bool operator == (const Sphere& dest);
	CollisionType CheckCollision(const Sphere& a, const Sphere& b);
};



