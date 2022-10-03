#pragma once
#include "GameCore.h"
#include "Scene.h"

class MapObject;
class Sound;
class Object2DComponent;
class SceneTitle : public Singleton<SceneTitle>, public Scene
{
private:
	Vector2D		_vCamera;
	MapObject* _pBackGround;
	MapObject* _pTitle;
	MapObject* _pPressAnyKey;
	Object2DComponent* _pMan;
	Object2DComponent* _pWoman;
	Object2DComponent* _pMan2;
	Sound* _pBackGroundMusic;
	
public:
	virtual void OnEnter();
	virtual void OnExecute();
	virtual void OnExit();
};

