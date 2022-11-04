#pragma once
#include "Sprite.h"

class Effect2D
{
public:
	TVector2   _vPos;
	TVector2   _vDir = { 0,-1 };
	float		_fLifeTime = 1.33f;
	float		_fSpeed = 300.0f;
	UINT		_iIndex = 0;
	UINT		_iMaxIndex = 1;
	float		_fEffectTimer = 0.0f;
	Rect		_tRect = { 0,0,0,0 };
	float		_fStep = 1.0f;
	Rect _rtCollision;
	Sprite* _pSprite = nullptr;//¸®¼Ò½º

public:
	Rect convert(RECT rt);
	virtual bool Update();
};
