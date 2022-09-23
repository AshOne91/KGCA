#pragma once
#include "Scene.h"
#include "SpriteManager.h"

struct Effect
{
	Vector2D   _vPos;
	Vector2D   _vDir = { 0,-1 };
	float		_fLifeTime = 1.33f;
	float		_fSpeed = 300.0f;
	UINT		_iIndex = 0;
	UINT		_iMaxIndex = 1;
	float		_fEffectTimer = 0.0f;
	Rect		_tRect = { 0,0,0,0 };
	float		_fStep = 1.0f;
	Rect _rtCollision;
	Sprite* _pSprite = nullptr;//¸®¼Ò½º

	Rect convert(RECT rt)
	{
		Rect tRt;
		tRt.x1 = rt.left;
		tRt.y1 = rt.top;
		tRt.w = rt.right;
		tRt.h = rt.bottom;
		return tRt;
	}
	virtual bool Update()
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

		Vector2D	vDrawSize;
		vDrawSize.x = _pSprite->_rtInit.w / 2.0f;
		vDrawSize.y = _pSprite->_rtInit.h / 2.0f;
		_rtCollision.Set(
			_vPos.x - vDrawSize.x,
			_vPos.y - vDrawSize.y,
			_pSprite->_rtInit.w,
			_pSprite->_rtInit.h);
		return true;
	}

};
struct Projectile : Effect
{
	virtual bool Update()
	{
		_fEffectTimer += g_fSecondPerFrame;
		if (_fLifeTime <= _fEffectTimer)
		{
			return false;
		}
		if (_fStep <= _fEffectTimer)
		{
			_fEffectTimer -= _fStep;
			_iIndex++;
		}
		if (_iIndex >= _iMaxIndex)
		{
			_iIndex = 0;
		}
		RECT rt = _pSprite->_uvArray[_iIndex];
		_tRect = convert(rt);
		Vector2D vAdd = _vDir * _fSpeed * g_fSecondPerFrame;
		_vPos = _vPos + vAdd;

		Vector2D	vDrawSize;
		vDrawSize.x = _pSprite->_rtInit.w / 2.0f;
		vDrawSize.y = _pSprite->_rtInit.h / 2.0f;
		_rtCollision.Set(
			_vPos.x - vDrawSize.x,
			_vPos.y - vDrawSize.y,
			_pSprite->_rtInit.w,
			_pSprite->_rtInit.h);
		return true;
	}
	Projectile()
	{
		_fLifeTime = 3.33f;
		_fSpeed = 600.0f;
	}
};
class SceneInGame : public Scene
{
public:
	Vector2D		_vCamera;
	MapObject* _pMap;
	User2D* _pUser;
	std::list<Effect*>		_pEffectList;
	std::list<Npc2D*>		_pNpcList;
	std::list<Projectile*>  _Projectile;
public:
	void AddProjectile(Vector2D pos);
	void AddEffect();
	void AddEffect(float x, float y);
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
	virtual void		DrawMiniMap(UINT x, UINT y, UINT w = 100, UINT h = 100);
};

