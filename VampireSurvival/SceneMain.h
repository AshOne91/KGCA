#pragma once
#include "Scene.h"

class User2DComponent;
class SceneMain : public Singleton<SceneMain>, public Scene
{
	User2DComponent* _pUser;
	Sound* _pBackGroundMusic;

public:
	virtual void OnEnter();
	virtual void OnExecute();
	virtual void OnExit();
};

