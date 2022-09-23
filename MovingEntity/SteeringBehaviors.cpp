#include "SteeringBehaviors.h"
#include "Vehicle.h"
#include "Utils.h"
#include "Transformations.h"
#include "Param.h"
#include "GameWorld.h"
#include "Wall2D.h"
#include "geometry.h"

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
				float ExpandedRadius = (*curOb)->BRadius() + _pVehicle->BRadius();

				if (fabs(LocalPos.y) < ExpandedRadius)
				{
					float cX = LocalPos.x;
					float cY = LocalPos.y;

					float SqrtPart = sqrt(ExpandedRadius * ExpandedRadius - cY * cY);

					float ip = cX - SqrtPart;

					if (ip <= 0)
					{
						ip = cX + SqrtPart;
					}

					if (ip < DistToClosetIP)
					{
						DistToClosetIP = ip;

						ClosestInterectingObstacle = *curOb;

						LocalPosOfClosestObstacle = LocalPos;
					}
				}
			}
		}

		++curOb;
	}

	Vector2D SteeringForce;

	if (ClosestInterectingObstacle)
	{
		// 가까울 수록 힘이 강해져야 함
		float multiplier = 1.0f + (_fDBoxLength - LocalPosOfClosestObstacle.x) / _fDBoxLength;

		// 옆방향힘을 계산한다.
		SteeringForce.y = (ClosestInterectingObstacle->BRadius() - LocalPosOfClosestObstacle.y) * multiplier;

		const float BrakingWeight = 0.2f;

		SteeringForce.x = (ClosestInterectingObstacle->BRadius() - LocalPosOfClosestObstacle.x) * BrakingWeight;
	}

	return VectorToWorldSpace(SteeringForce, _pVehicle->Heading(), _pVehicle->Side());
}

void SteeringBehaviors::CreateFeelers()
{
	_Feelers[0] = _pVehicle->_vPos + _fWallDetectionFeelerLength * _pVehicle->Heading();

	Vector2D temp = _pVehicle->Heading();
	Vec2DRotateAroundOrigin(temp, KSHCore::UTIL::HalfPi * 3.5f);
	_Feelers[1] = _pVehicle->_vPos + _fWallDetectionFeelerLength / 2.0f * temp;
	
	temp = _pVehicle->Heading();
	Vec2DRotateAroundOrigin(temp, KSHCore::UTIL::HalfPi * 0.5f);
	_Feelers[2] = _pVehicle->_vPos + _fWallDetectionFeelerLength / 2.0f * temp;

}

Vector2D SteeringBehaviors::WallAvoidance(const std::vector<Wall2D>& walls)
{
	CreateFeelers();

	float DistToThisIP = 0.0f;
	float DistToClosestIP = KSHCore::UTIL::MaxFloat;

	int ClosestWall = -1;

	Vector2D SteeringForce;
	Vector2D point;
	Vector2D ClosestPoint;

	for (unsigned int flr = 0; flr < _Feelers.size(); ++flr)
	{
		for (int w = 0; w < walls.size(); ++w)
		{
			if (LineIntersection2D(_pVehicle->_vPos, _Feelers[flr], walls[w].From(), walls[w].To(), DistToThisIP, point))
			{
				if (DistToThisIP < DistToClosestIP)
				{
					DistToClosestIP = DistToThisIP;

					ClosestWall = w;

					ClosestPoint = point;
				}
			}
		}

		if (ClosestWall >= 0)
		{
			Vector2D OverShoot = _Feelers[flr] - ClosestPoint;

			SteeringForce = walls[ClosestWall].Normal() * OverShoot.Length();
		}
	}

	return SteeringForce;
}

Vector2D SteeringBehaviors::Interpose(const Vehicle* AgentA, const Vehicle* AgentB)
{
	Vector2D MidPoint = (AgentA->_vPos + AgentB->_vPos) / 2.0f;

	float TimeToReachMidPoint = Vector2D::Distance(_pVehicle->_vPos, MidPoint) / _pVehicle->MaxSpeed();

	Vector2D APos = AgentA->_vPos + AgentA->Velocity() * TimeToReachMidPoint;
	Vector2D BPos = AgentB->_vPos + AgentB->Velocity() * TimeToReachMidPoint;

	MidPoint = (APos + BPos) / 2.0f;

	return Arrive(MidPoint, Deceleration::fast);
}

Vector2D SteeringBehaviors::GetHidingPosition(const Vector2D& posOb, const float radiusOb, const Vector2D& posTarget)
{
	const float DistanceFromBoundary = 30.0f;
	
	float DistAway = radiusOb + DistanceFromBoundary;

	Vector2D ToOb(posOb - posTarget);
	ToOb.Identity();

	return (ToOb * DistAway) + posOb;
}

Vector2D SteeringBehaviors::Hide(const Vehicle* target, std::vector<BaseGameEntity*>& obstacles)
{
	float DistToClosest = KSHCore::UTIL::MaxFloat;
	Vector2D BestHidingSpot;

	auto curOb = obstacles.begin();
	while (curOb != obstacles.end())
	{
		Vector2D HidingSpot = GetHidingPosition((*curOb)->Pos(), (*curOb)->BRadius(), target->_vPos);

		float dist = Vector2D::DistanceSq(HidingSpot, _pVehicle->_vPos);

		if (dist < DistToClosest)
		{
			DistToClosest = dist;

			BestHidingSpot = HidingSpot;
		}

		++curOb;
	}

	if (DistToClosest == KSHCore::UTIL::MaxFloat)
	{
		return Evade(target);
	}

	return Arrive(BestHidingSpot, Deceleration::fast);
}

Vector2D SteeringBehaviors::FollowPath()
{
	if (Vector2D::DistanceSq(_pPath->CurrentWayPoint(), _pVehicle->_vPos) < _WayPointSeekDistSq)
	{
		_pPath->SetNextWayPoint();
	}

	if (!_pPath->Finished())
	{
		return Seek(_pPath->CurrentWaypoint());
	}
	else
	{
		return Arrive(_pPath->CurrentWaypoint(), Deceleration::normal);
	}
}

Vector2D SteeringBehaviors::OffsetPursuit(const Vehicle* leader, const Vector2D offset)
{
	Vector2D WorldOffsetPos = PointToWorldSpace(offset, leader->Heading(), leader->Side(), leader->_vPos);

	Vector2D ToOffset = WorldOffsetPos - _pVehicle->_vPos;

	float LookAheadTime = ToOffset.Length() / (_pVehicle->MaxSpeed() + leader->Speed());

	return Arrive(WorldOffsetPos + leader->Velocity() * LookAheadTime, Deceleration::fast);
}

Vector2D SteeringBehaviors::Separation(const std::vector<Vehicle*>& neighbors)
{
	Vector2D SteeringForce;

	for (int a = 0; a < neighbors.size(); ++a)
	{
		if ((neighbors[a] != _pVehicle) && neighbors[a]->IsTagged())
		{
			Vector2D ToAgent = _pVehicle->_vPos - neighbors[a]->_vPos;

			SteeringForce += ((ToAgent.Identity()) / ToAgent.Length());
		}
	}

	return SteeringForce;
}

Vector2D SteeringBehaviors::Alignment(const std::vector<Vehicle*>& neighbors)
{
	return Vector2D();
}

Vector2D SteeringBehaviors::Cohesion(const std::vector<Vehicle*>& neighbors)
{
	return Vector2D();
}


