#pragma once
#include "GameCore.h"
#include "Scene.h"

class MapObject;
class Sound;
class Object2DComponent;
class SceneEnd : public Singleton<SceneEnd>, public Scene
{
private:
	Vector2D		_vCamera;
	MapObject* _pBackGround;
	MapObject* _pTitle;
	MapObject* _pPressAnyKey;
	Sound* _pBackGroundMusic;

public:
	virtual void OnEnter();
	virtual void OnExecute();
	virtual void OnExit();
};

