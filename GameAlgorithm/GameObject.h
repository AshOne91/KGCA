#pragma once
#include <unordered_map>
#include "Collison.h"

class GameApp;
class Behaviors;
class GameObject
{
public:
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

private:
	static unsigned __int64 _AllocObjectIdx;

protected:
	GameApp* m_App;
	Behaviors* m_Behaviors;

	enObjectType m_ObjectType;
	unsigned __int64 m_Faction;

public:
	std::string _name;

public:
	Box3D _box3d;
	Sphere _sphere;

protected:
	Vector3D _pos;
	float _radius;
	Vector3D velocity;
	Vector3D _heading;
	float _maxSpeed;

	enActive m_Active = enActive::InActive;
	unsigned __int64 m_ObjectIdx;

public:
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