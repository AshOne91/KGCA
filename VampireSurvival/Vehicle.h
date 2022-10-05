#pragma once
#include "MovingEntity.h"

class SteeringBehaviors;
class Vehicle : public MovingEntity
{
private:
	bool _bTag = false;
	SteeringBehaviors* _pSteering;

public:
	void Update(float time_elapsed);
	void SetTag(bool bTag)
	{
		_bTag = bTag;
	}
	bool IsTagged()
	{
		return _bTag;
	}
	SteeringBehaviors* GetSteeringBehaviours() { return _pSteering; }

public:
	Vehicle();
	virtual ~Vehicle();
};

