#pragma once
#include "Scene.h"

class SceneInGame : public Scene
{
public:
	MapObject* _pMap;
	std::vector<Npc2D*> _pNpcList;
	std::vector<Texture*> _ObjectTextureList;

public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	virtual void DrawMinMap(UINT x, UINT y, UINT w = 100, UINT h = 100);
};

