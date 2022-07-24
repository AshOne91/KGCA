#pragma once
#include "SceneController.h"
#include "enum.h"

class SceneLoad : public SceneController<SceneLoad>
{
public:
	SceneLoad();
	virtual ~SceneLoad();

public:
	virtual void Construct();
	virtual void Destruct();

protected:
	virtual void OnEnter();
	virtual void OnLeave();
	virtual void DoUpdate();
};
