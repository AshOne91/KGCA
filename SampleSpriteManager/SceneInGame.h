#pragma once
#include "Scene.h"

class SceneInGame : public Scene
{
public:
	MapObject* _pMap;
	std::vector<Npc2D*>		_pNpcList;
	std::vector<Texture*>		_ObjectTextureList;
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
	virtual void		DrawMiniMap(UINT x, UINT y, UINT w = 100, UINT h = 100);
};



