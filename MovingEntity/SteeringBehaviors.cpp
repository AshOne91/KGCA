#include "SteeringBehaviors.h"
#include "Vehicle.h"
#include "Utils.h"
#include "Transformations.h"
#include "Param.h"
#include "GameWorld.h"

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

	// 목표 지점까지의 거리를 계산
	float dist = ToTarget.Length();

	if (dist > 0)
	{
		//감속이 열거된 정수이므로, 미세조정된 감속을 제공하기 위해 이값을 요구
		const float DecelerationTweaker = 0.3f;

		float speed = dist / ((float)deceleration * DecelerationTweaker);
		speed = (std::min)(speed, _pVehicle->_fMaxSpeed);

		//dist를 구했으므로 정규화가 필요 없음
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

Vector2D SteeringBehaviors::Wander()
{
	_vWanderTarget += Vector2D(KSHCore::UTIL::RandomClamped() * _fWanderJitter, KSHCore::UTIL::RandomClamped() * _fWanderJitter);
	_vWanderTarget.Normalize();
	_vWanderTarget *= _fWanderRadius;

	Vector2D targetLocal = _vWanderTarget + Vector2D(_fWanderDistance, 0);

	Vector2D targetWorld = PointToWorldSpace(targetLocal,
		_pVehicle->Heading(),
		_pVehicle->Side(),
		_pVehicle->_vPos);

	return targetWorld - _pVehicle->_vPos;
}

Vector2D SteeringBehaviors::ObstacleAvoidance(const std::vector<BaseObject*>& obstacles)
{
	_fDBoxLength = Prm.MinDetectionBoxLength + (_pVehicle->Speed() / _pVehicle->MaxSpeed()) * Prm.MinDetectionBoxLength;

	_pVehicle->World()->TagObstaclesWithinViewRange(_pVehicle, _fDBoxLength);

	BaseObject* ClosestInterectingObstacle = nullptr;

	float DistToClosetIP = KSHCore::UTIL::MaxFloat;

	Vector2D LocalPosOfClosestObstacle;

	std::vector<BaseObject*>::const_iterator curOb = obstacles.begin();

	while (curOb != obstacles.end())
	{
		if ((*curOb)->IsTagged())
		{
			Vector2D LocalPos = PointToLocalSpace((*curOb)->Pos(), _pVehicle->Heading(), _pVehicle->Side(), _pVehicle->_vPos());

			if (LocalPos.x >= 0)
			{
				float ExpandedRadius = (*curOb)->BRadius() + 
			}
		}
	}





	return Vector2D();
}
