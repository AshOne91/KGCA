#pragma once
#include "Scene.h"

class User2DComponent;
class SceneMain : public Singleton<SceneMain>, public Scene
{
	User2DComponent* _pUser = nullptr;
	Sound* _pBackGroundMusic = nullptr;
	unsigned __int64 monsterTextIndex = 0;
	unsigned __int64 hpTextIndex = 0;
	unsigned __int64 remainTimeTextIndex = 0;
	float _fTimer = 0;

public:
	virtual void OnEnter();
	virtual void OnExecute();
	virtual void OnExit();
};

