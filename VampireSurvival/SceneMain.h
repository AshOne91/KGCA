#pragma once
#include "Scene.h"

class SceneMain : public Singleton<SceneMain>, public Scene
{
public:
	virtual void OnEnter();
	virtual void OnExecute();
	virtual void OnExit();
};

