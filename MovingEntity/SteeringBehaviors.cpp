#include "SteeringBehaviors.h"
#include "Vehicle.h"

Vector2D SteeringBehaviors::Seek(Vector2D TargetPos)
{

	Vector2D DesiredVelocity = (TargetPos - _pVehicle->_vPos).Identity() * _pVehicle->_fMaxSpeed;
	return (DesiredVelocity - _pVehicle->_vVelocity);
}

Vector2D SteeringBehaviors::Flee(Vector2D TargetPos)
{
	const float PanicDistanceSq = 100.0f * 100.0f;
	if (Vector2D::DistanceSq(_pVehicle->_vPos, TargetPos) > PanicDistanceSq)
	{
		return Vector2D(0, 0);
	}

	Vector2D DesiredVelocity = (_pVehicle->_vPos - TargetPos).Identity() * _pVehicle->_fMaxSpeed;
	return (DesiredVelocity - _pVehicle->_vVelocity);
}

Vector2D SteeringBehaviors::Arrive(Vector2D TargetPos, Deceleration deceleration)
{
	Vector2D ToTarget = TargetPos - _pVehicle->_vPos;

	// ��ǥ ���������� �Ÿ��� ���
	float dist = ToTarget.Length();

	if (dist > 0)
	{
		//������ ���ŵ� �����̹Ƿ�, �̼������� ������ �����ϱ� ���� �̰��� �䱸
		const float DecelerationTweaker = 0.3f;

		float speed = dist / ((float)deceleration * DecelerationTweaker);
		speed = (std::min)(speed, _pVehicle->_fMaxSpeed);

		//dist�� �������Ƿ� ����ȭ�� �ʿ� ����
		Vector2D DesiredVelocity = ToTarget * speed / dist;

		return (DesiredVelocity - _pVehicle->_vVelocity);
	}
	return Vector2D();
}

Vector2D SteeringBehaviors::Pursuit(const Vehicle* evader)
{
	Vector2D ToEvader = evader->_vPos - _pVehicle->_vPos;

	float RelativeHeading = _pVehicle->_vHeading.Dot(evader->_vHeading);
	if ((ToEvader.Dot(_pVehicle->_vHeading)) > 0 && (RelativeHeading < -0.95))
	{
		return Seek(evader->_vPos);
	}

	float LookAheadTime = ToEvader.Length() / (_pVehicle->_fMaxSpeed + evader->Speed());

	return Seek(evader->_vPos + evader->Velocity() * LookAheadTime);
}

Vector2D SteeringBehaviors::Evade(const Vehicle* pursuer)
{
	Vector2D ToPursuer = pursuer->_vPos - _pVehicle->_vPos;
	float LookAheadTime = ToPursuer.Length() / (_pVehicle->MaxSpeed() + pursuer->Speed());
	return Flee(pursuer->_vPos + pursuer->Velocity() * LookAheadTime);
}

float SteeringBehaviors::TurnaroundTIme(const Vehicle* pAgent, const Vector2D& TargetPos)
{
	Vector2D toTarget(TargetPos - pAgent->_vPos);
	toTarget.Normalize();

	float dot = pAgent->Heading().Dot(toTarget);

	const float coefficient = 0.5f;
	return (dot - 1.0f) * -coefficient;
}
