#include "Missile.h"
#include "GameApp.h"
#include "Behaviors.h"
#include <limits>

Missile::Missile(GameApp* app, unsigned __int64 faction, Vector3D pos, Vector3D size)
	:GameObject(app, enObjectType::Missile, faction, pos, size)
{
	_maxSpeed = 1.5f;
}

Missile::~Missile()
{
}

void Missile::Update(float dt)
{
	GameObject* target = GetApp()->GetObject(m_TargetIdx);
	Vector3D pos = GetPosition();
	if (target == nullptr)
	{
		auto monsterObjects = GetApp()->GetObjects(GetPosition(), 50.0f, (unsigned __int64)enFaction::Monster);
		float minDistance = (std::numeric_limits<float>::max)();
		for (auto obj : monsterObjects)
		{
			Vector3D toTarget = obj->GetPosition() - GetPosition();
			//if (toTarget.Dot(GetHeading()) > 0.0f)
			//{
				//if (obj == this)
					//continue;

			if (obj->GetActive() != enActive::Active)
				continue;

			float disq = Vector3D::DistanceSq(obj->GetPosition(), GetPosition());
			if (minDistance > disq)
			{
				minDistance = disq;
				m_TargetIdx = obj->GetObjectIdx();
				target = obj;
			}
			//}
		}
	}

	Vector3D force = GetBehaviors()->Calculate(target);
	Vector3D accel = force / 1.0f;
	_velocity += accel * dt;
	if (_velocity.Length() > _maxSpeed)
	{
		_velocity = _velocity.Identity();
		_velocity *= _maxSpeed;
	}

	pos += _velocity * dt;
	_heading = _velocity.Identity();

	SetPosition(pos);

	if (target != nullptr)
	{
		if (Vector3D::DistanceSq(GetPosition(), target->GetPosition()) <= (target->_sphere.radius * target->_sphere.radius) + (target->_sphere.radius * target->_sphere.radius))
		{
			GetApp()->Destroy(target);
			GetApp()->Destroy(this);
		}
	}
}
