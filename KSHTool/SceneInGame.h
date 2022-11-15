#pragma once
#include "Scene.h"
#include "SpriteManager.h"
#include "Projectile2D.h"

class SceneInGame : public Scene
{
public:
	TVector2		_vCamera;
	MapObject* _pMap;
	User2D* _pUser;
	std::list<Effect2D*>		_pEffectList;
	std::list<Npc2D*>		_pNpcList;
	std::list<Projectile2D*>  _Projectile;
public:
	void AddProjectile(TVector2 pos);
	void AddEffect();
	void AddEffect(float x, float y);
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
	virtual void		DrawMiniMap(UINT x, UINT y, UINT w = 100, UINT h = 100);
};

