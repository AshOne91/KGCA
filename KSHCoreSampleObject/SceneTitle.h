#pragma once
#include "Scene.h"

class SceneTitle: public Scene
{
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
};

