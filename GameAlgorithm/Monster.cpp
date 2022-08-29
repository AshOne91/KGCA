#include "Monster.h"
#include "GameApp.h"

Monster::Monster(GameApp* app, unsigned __int64 faction, Vector3D pos, Vector3D size)
	:GameObject(app, enObjectType::Monster, faction, pos, size)
{
	_velocity.y = 1.0f;
}

Monster::~Monster()
{
}

void Monster::Update(float dt)
{
	Vector3D pos = GetPosition();
	if (_velocity.Length() > _maxSpeed)
	{
		_velocity = _velocity.Identity();
		_velocity *= _maxSpeed;
	}

	pos += _velocity * dt;
	_heading = _velocity.Identity();

	SetPosition(pos);

	if (CheckRangeOut(_pos.x, _pos.y))
	{
		GetApp()->Destroy(this);
	}
}
