#pragma once
#include "SceneController.h"
#include "enum.h"

class SceneSave : public SceneController<SceneSave>
{
public:
	SceneSave();
	virtual ~SceneSave();

public:
	virtual void Construct();
	virtual void Destruct();

protected:
	virtual void OnEnter();
	virtual void OnLeave();
	virtual void DoUpdate();
};
