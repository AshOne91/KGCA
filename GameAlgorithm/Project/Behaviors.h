#pragma once
#include "GameObject.h"
#include "Vector.h"

class Behaviors
{
public:
	Behaviors(GameObject* object)
		: m_Owner(object)
	{}
	~Behaviors()
	{}

public:
	Vector3D Calculate(GameObject* target)
	{
		m_vForce.Zero();
		if (target != nullptr)
		{
			m_vForce += _Pursuit(target);
		}

		return m_vForce;
	}

private:
	Vector3D _Seek(Vector3D targetPos)
	{
		Vector3D toTarget = targetPos - m_Owner->GetPosition();
		Vector3D velocity = toTarget.Identity() * m_Owner->GetMaxSpeed();
		return velocity - m_Owner->GetVelocity();
	}

	Vector3D _Pursuit(GameObject* target)
	{
		Vector3D toTarget = target->GetPosition() - m_Owner->GetPosition();
		float RelativeHeading = m_Owner->GetHeading().Dot(target->GetHeading());
		Vector3D targetHeading = target->GetHeading();

		if (toTarget.Dot(m_Owner->GetHeading()) > 0 &&
			m_Owner->GetHeading().GetDegreeBetweenVectorDot(targetHeading) < 18.0f)
		{
			return _Seek(target->GetPosition());
		}

		float lookAhead = toTarget.Length() / m_Owner->GetMaxSpeed();
		return _Seek(target->GetPosition() + target->GetVelocity() * lookAhead);
	}



private:
	Vector3D m_vForce;
	GameObject* m_Owner;
};
