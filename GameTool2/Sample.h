#pragma once
#include "GameCore.h"
#include "Scene.h"
#include "SceneInGame.h"
#include "SceneTitle.h"
#include "Quadtree.h"

class Sample : public GameCore
{
public:
	std::shared_ptr<SceneTitle> _pTitle = nullptr;
	std::shared_ptr<SceneInGame> _pInGame = nullptr;
	std::shared_ptr<Scene> _pCurrentScene = nullptr;
	Quadtree _Quadtree;

public:
	virtual bool		Init() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
	virtual bool		Release() override;
	virtual HRESULT CreateDXResource() override;
};

