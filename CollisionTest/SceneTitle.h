#pragma once
#include "Scene.h"

class SceneTitle : public Scene
{
public:
	User2D* _pUser;
	BaseObject* _pMapTitle;
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
};

