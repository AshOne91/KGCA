#pragma once
#include "GameCore.h"
#include "Scene.h"
#include "SceneInGame.h"
#include "SceneTitle.h"

class Sample : public GameCore
{
public:
	SceneTitle* _pTitle = nullptr;
	SceneInGame* _pInGame = nullptr;
	Scene* _pCurrentScene = nullptr;

public:
	virtual bool		Init() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
	virtual bool		Release() override;
};

