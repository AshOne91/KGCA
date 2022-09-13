#pragma once
#include <BaseObject.h>
#include "C2DMatrix.h"

class MovingEntity : public BaseObject
{
public:
	Vector2D _vPos;
	Vector2D _vVelocity;
	Vector2D _vHeading;
	Vector2D _vSide;

	float _fMass;
	float _fMaxSpeed;
	float _fMaxForce;
	float _fMaxTurnRate;

public:
	Vector2D Velocity() const
	{
		return _vVelocity;
	}
	void SetVelocity(const Vector2D vel)
	{
		_vVelocity = vel;
	}

	float Mass() const
	{
		return _fMass;
	}
	Vector2D Side() const
	{
		return _vSide;
	}

	float MaxSpeed() const
	{
		return _fMaxSpeed;
	}
	void SetMaxSpeed(float maxSpeed)
	{
		_fMaxSpeed = maxSpeed;
	}

	bool IsSpeedMaxedOut() const
	{
		return (_fMaxSpeed * _fMaxSpeed) >= _vVelocity.LengthSq();
	}
	float Speed() const
	{
		return _vVelocity.Length();
	}
	float SpeedSq() const
	{
		return _vVelocity.LengthSq();
	}

	Vector2D Heading() const
	{
		return _vHeading;
	}
	void SetHeading(Vector2D newHeading)
	{
		_vHeading = newHeading;
		_vSide = _vHeading.Perp();
	}
	bool RotateHeadingToFacePosition(Vector2D target)
	{
		Vector2D toTarget = target - _vPos;
		toTarget.Normalize();

		float angle = _vHeading.GetRadianBetweenVectorDot(toTarget);

		if (angle < Epsilon) return true;

		if (angle > _fMaxTurnRate)
		{
			angle = _fMaxTurnRate;
		}

		C2DMatrix RotationMatrix;

		RotationMatrix.Rotate(angle * (int)_vHeading.Sign(toTarget));
		RotationMatrix.TransformVector2Ds(_vHeading);
		RotationMatrix.TransformVector2Ds(_vVelocity);

		_vSide = _vHeading.Perp();

		return true;
	}

	float MaxTurnRate() const
	{
		return _fMaxTurnRate;
	}
	void SetMaxTurnRate(double val)
	{
		_fMaxTurnRate = val;
	}


};

