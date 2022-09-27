#pragma once
#include "Scene.h"
#include "Interface.h"

class SceneTitle : public Scene
{
public:
	User2D* _pUser;
	BaseObject* _pMapTitle;
	Interface* _FadeObject;
	Interface* _btnStart;
	Interface* _listControl;
	Interface* _Dlg;

public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();

public:
	virtual bool IsNextScene();
};

