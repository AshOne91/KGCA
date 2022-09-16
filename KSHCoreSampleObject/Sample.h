#pragma once
#include "GameCore.h"
#include "SceneTitle.h"
#include "SceneInGame.h"

class Sample : public GameCore
{
public:
	SceneTitle* _pTitle = nullptr;
	SceneInGame* _pInGame = nullptr;
	Scene* _pCurrentScene = nullptr;

public:
	virtual bool Init() final;
	virtual bool Frame() final;
	virtual bool Render() final;
	virtual bool Release() final;
};
