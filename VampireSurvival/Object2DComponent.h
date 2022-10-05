#pragma once
#include "Object2D.h"
#include "Component.h"
#include "Vehicle.h"

class Sprite;
class Object2DComponent : public Object2D, public Vehicle, public ComponentObject
{
public:
	bool _bFlip = false;
	bool _bAnimation = false;
	Sprite* _pSprite = nullptr;
	float		_fLifeTime = 1.33f;
	float		_fSpeed = 300.0f;
	UINT		_iIndex = 0;
	UINT		_iMaxIndex = 1;
	float		_fEffectTimer = 0.0f;
	Rect		_tRect = { 0,0,0,0 };
	float		_fStep = 1.0f;
public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;

public:
	virtual Rect convert(RECT rt);
	virtual bool EffectUpdate();
	virtual bool InitSprite();
};

