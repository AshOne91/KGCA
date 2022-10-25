#pragma once
#include <Windows.h>
#include <math.h>

#define ASH_EPSILON ((FLOAT) 0.001f)
#define ASH_PI ((FLOAT) 3.141592654f)
#define DegreeToRadian(degree) ((degree) * (ASH_PI / 180.0f))
#define RadianToDegree(radian) ((radian) * (180.0f / ASH_PI))
#define MAKECOLOR_ARGB(a, r, g, b) (((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)
#define IS_IN_RANGE()