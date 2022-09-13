#pragma once
#include "MovingEntity.h"

class GameWorld;
class SteeringBehaviors;
class Vehicle : public MovingEntity
{
private:
	GameWorld* _pWorld;
	SteeringBehaviors* _pSteering;

public:
	void Update(float time_elapsed);
};

