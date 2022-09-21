#pragma once
#include "GameCore.h"
#include "User2D.h"
#include "MapObject.h"
#include "SpriteManager.h"

struct Effect
{
	Vector2D _vPos;
	Vector2D _vDir = { 0, 1 };
	float _fLifeTime = 1.33f;
	float _fSpeed = 300.0f;
	UINT _iIndex = 0;
	UINT _iMaxIndex = 1;
	float _fEffectTimer = 0.0f;
	Rect _tRect = { 0, 0, 0, 0 };
	float _fStep = 1.0f;
	Rect _rtCollision;
	Sprite* _pSprite = nullptr;

	Rect convert(RECT rt)
	{
		Rect tRt;
		tRt.x1 = rt.left;
		tRt.y1 = rt.top;
		tRt.w = rt.right;
		tRt.h = rt.bottom;
		return tRt;
	}

	bool Update()
	{
		_fEffectTimer += g_fSecondPerFrame;
		if (_fStep <= _fEffectTimer)
		{
			_fEffectTimer -= _fStep;
			_iIndex++;
		}
		if (_iIndex >= _iMaxIndex)
		{
			return false;
		}
		RECT rt = _pSprite->_uvArray[_iIndex];
		_tRect = convert(rt);
		Vector2D vAdd = _vDir * _fSpeed * g_fSecondPerFrame;
		_vPos = _vPos + vAdd;
		_rtCollision.x1 = _vPos.x;
		_rtCollision.y1 = _vPos.y;
		return true;
	}
};

class Sample : public GameCore
{
	Vector2D		_vCamera;
	MapObject* _pMap;
	User2D* _pUser;
	Sprite* _pObject;

	std::list<Effect*> _pEffectList;
public:
	void AddEffect();
	virtual bool		Init() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
	virtual bool		Release() override;
};
