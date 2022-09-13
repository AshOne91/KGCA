#pragma once
#include "Vector.h"

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
	// ������Ʈ �տ� ��ȸ�ϱ� ���� ����Ǵ� �Ÿ�
	float _fWanderJitter;
	// �����ϴ� ���� �ݰ�
	float _fWanderRadius;
	// ����Ǵ� ���� ����Ÿ�
	float _fWanderDistance;

public:
	Vehicle* _pVehicle;
	Vector2D Seek(Vector2D TargetPos);
	Vector2D Flee(Vector2D TargetPos);
	Vector2D Arrive(Vector2D TargetPos, Deceleration deceleration);
	Vector2D Pursuit(const Vehicle* evader);
	Vector2D Evade(const Vehicle* pursuer);

	static float TurnaroundTIme(const Vehicle* pAgent, const Vector2D& TargetPos);
};

