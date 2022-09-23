#pragma once
#include "Scene.h"
#include "Interface.h"

class SceneTitle : public Scene
{
public:
	User2D* _pUser;
	BaseObject* _pMapTitle;
	Interface* _btnStart;
	ListControl* _listControl;
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();

public:
	virtual bool IsNextScene();
};

