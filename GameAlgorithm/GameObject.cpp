#include "GameApp.h"
#include "GameObject.h"
#include "Behaviors.h"

unsigned __int64 GameObject::_AllocObjectIdx = 0;

GameObject::GameObject(GameApp* app, enObjectType type, unsigned __int64 faction, Vector3D pos, Vector3D size)
	: _app(app)
	, _objectType(type)
	, _faction(faction)
	, _objectIdx(++_AllocObjectIdx)
	, _active(enActive::Active)
	, _maxSpeed(1.0f)
{
	_box3d.Set(pos, size);
	_sphere.Set(_box3d);
	_pos = _sphere.center;
	_radius = _sphere.radius;
	_behaviors = new Behaviors(this);
}

GameObject::~GameObject()
{
	delete _behaviors;
}

GameApp* GameObject::GetApp()
{
	return _app;
}

Behaviors* GameObject::GetBehaviors()
{
	return _behaviors;
}

unsigned __int64 GameObject::GetFaction()
{
	return _faction;
}

bool GameObject::CheckFaction(unsigned __int64 otherFaction)
{
	if ((_faction & otherFaction))
	{
		return true;
	}
	return false;
}

void GameObject::SetPosition(Vector3D position)
{
	Vector3D diff = position - _pos;
	_pos = position;
	_sphere.Set(position, _radius);
	_box3d.Set(_box3d.min + diff, _box3d.size);
}

Vector3D GameObject::GetPosition()
{
	return _pos;
}

Vector3D GameObject::GetVelocity()
{
	return _velocity;
}

float GameObject::GetMaxSpeed()
{
	return _maxSpeed;
}

Vector3D GameObject::GetHeading()
{
	return _heading;
}

enActive GameObject::GetActive()
{
	return _active;
}

void GameObject::SetActive(enActive active)
{
	_active = active;
}

enObjectType GameObject::GetType()
{
	return _objectType;
}

unsigned __int64 GameObject::GetObjectIdx()
{
	return _objectIdx;
}
