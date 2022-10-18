#pragma once
#include "Scene.h"
#include "Interface.h"
#include "Projectile2D.h"
#include "Shape.h"
#include "Camera.h"
#include "Map.h"

class SceneTitle : public Scene
{
public:
	User2D* _pUser;
	BaseObject* _pBG;
	Interface* _FadeObject;
	Interface* _btnStart;
	Interface* _btnStart2;
	Interface* _listControl;
	Interface* _Dlg;
	Map* _pMap = nullptr;
	ShapeBox* _pBoxObjA = nullptr;
	ShapeBox* _pBoxObjB = nullptr;
	Camera* _pMainCamera = nullptr;

public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();

public:
	virtual bool IsNextScene();
};

