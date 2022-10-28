#pragma once
#include "AshMath.h"

enum class PointPosition
{
	CP_FRONT,
	CP_BACK,
	CP_ONPLANE,
	CP_SPANNING
};

class Collision
{
public:
	TVector3 _vBackPosition;
	TVector3 _vPosition;

};
