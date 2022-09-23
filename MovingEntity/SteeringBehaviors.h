#pragma once
#include "Vector.h"
#include "BaseObject.h"

enum class Deceleration : int
{
	slow = 3, 
	normal = 2,
	fast = 1
};
class Vehicle;
class SteeringBehaviors
{
private:
	Vector2D _vWanderTarget;

	// 에이전트 앞에 배회하기 원이 투사되는 거리
	float _fWanderJitter;
	// 제한하는 원의 반경
	float _fWanderRadius;
	// 투사되는 원의 투사거리
	float _fWanderDistance;

	float _fDBoxLength;

	std::vector<Vector2D> _Feelers;

	float _fWallDetectionFeelerLength;

public:
	Vehicle* _pVehicle;
	Vector2D Seek(Vector2D TargetPos);
	Vector2D Flee(Vector2D TargetPos);
	Vector2D Arrive(Vector2D TargetPos, Deceleration deceleration);
	Vector2D Pursuit(const Vehicle* evader);
	Vector2D Evade(const Vehicle* pursuer);
	Vector2D Wander();
	Vector2D ObstacleAvoidance(const std::vector<BaseObject*>& obstacles);
	Vector2D WallAvoidance(const std::vector<Wall2D>& walls);
	Vector2D Interpose(const Vehicle* AgentA, const Vehicle* AgentB);

	void CreateFeelers();

	static float TurnaroundTIme(const Vehicle* pAgent, const Vector2D& TargetPos);
};

