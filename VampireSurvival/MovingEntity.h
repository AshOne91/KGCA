#pragma once
#include "Object2D.h"
#include "Vector.h"

class MovingEntity
{
public:
	Vector2D _vMovingPos;
	Vector2D _vVelocity;
	Vector2D _vHeading;
	Vector2D _vSide;

	float _fMass;
	float _fMaxSpeed;
	float _fMaxForce;
	float _fMaxTurnRate;

public:
	Vector2D Velocity() const;
	void SetVelocity(const Vector2D vel);

	float Mass() const;
	Vector2D Side() const;

	float MaxSpeed() const;
	void SetMaxSpeed(float maxSpeed);

	bool IsSpeedMaxedOut() const;
	float Speed() const;
	float SpeedSq() const;

	Vector2D Heading() const;
	void SetHeading(Vector2D newHeading);
	bool RotateHeadingToFacePosition(Vector2D target);

	float MaxTurnRate() const;
	void SetMaxTurnRate(double val);
};

