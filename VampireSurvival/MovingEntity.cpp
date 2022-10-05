#include "MovingEntity.h"
#include "C2DMatrix.h"

Vector2D MovingEntity::Velocity() const
{
	return _vVelocity;
}
void MovingEntity::SetVelocity(const Vector2D vel)
{
	_vVelocity = vel;
}

float MovingEntity::Mass() const
{
	return _fMass;
}
Vector2D MovingEntity::Side() const
{
	return _vSide;
}

float MovingEntity::MaxSpeed() const
{
	return _fMaxSpeed;
}
void MovingEntity::SetMaxSpeed(float maxSpeed)
{
	_fMaxSpeed = maxSpeed;
}

bool MovingEntity::IsSpeedMaxedOut() const
{
	return (_fMaxSpeed * _fMaxSpeed) >= _vVelocity.LengthSq();
}
float MovingEntity::Speed() const
{
	return _vVelocity.Length();
}
float MovingEntity::SpeedSq() const
{
	return _vVelocity.LengthSq();
}

Vector2D MovingEntity::Heading() const
{
	return _vHeading;
}
void MovingEntity::SetHeading(Vector2D newHeading)
{
	_vHeading = newHeading;
	_vSide = _vHeading.Perp();
}
bool MovingEntity::RotateHeadingToFacePosition(Vector2D target)
{
	Vector2D toTarget = target - _vMovingPos;
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

float MovingEntity::MaxTurnRate() const
{
	return _fMaxTurnRate;
}
void MovingEntity::SetMaxTurnRate(double val)
{
	_fMaxTurnRate = val;
}
