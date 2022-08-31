#pragma once
#include <unordered_map>
#include "Collison.h"

enum class enFaction : unsigned __int64
{
	Player = 1 << 0,
	Monster = 1 << 1
};

enum class enObjectType : int
{
	Player = 0,
	Monster = 1,
	Missile = 2
};

enum class enActive : int
{
	InActive = 0,
	Active = 1,
	Destroy = 2
};

class GameApp;
class Behaviors;
class Node;
class GameObject
{
public:
	GameObject(GameApp* app, enObjectType type, unsigned __int64 faction, Vector3D pos, Vector3D size);
	virtual ~GameObject();

private:
	static unsigned __int64 _AllocObjectIdx;

protected:
	GameApp* _app;
	Behaviors* _behaviors;

	enObjectType _objectType;
	unsigned __int64 _faction;

public:
	std::string _name;

public:
	Box3D _box3d;
	Box2D _box2D;
	Sphere _sphere;
	Node* _pNode = nullptr;

protected:
	Vector3D _pos;
	float _radius;
	Vector3D _velocity;
	Vector3D _heading;
	float _maxSpeed;

	enActive _active = enActive::InActive;
	unsigned __int64 _objectIdx;

public:
	GameApp* GetApp();
	Behaviors* GetBehaviors();

	virtual void Update(float dt) = 0;
	unsigned __int64 GetFaction();
	bool CheckFaction(unsigned __int64 otherFaction);
	void SetPosition(Vector3D position);
	Vector3D GetPosition();
	Vector3D GetVelocity();
	float GetMaxSpeed();
	Vector3D GetHeading();
	enActive GetActive();
	void SetActive(enActive active);
	enObjectType GetType();
	unsigned __int64 GetObjectIdx();
};