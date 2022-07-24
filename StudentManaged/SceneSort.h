#pragma once
#include "SceneController.h"
#include "enum.h"

class SceneSort : public SceneController<SceneSort>
{
public:
	SceneSort();
	virtual ~SceneSort();

public:
	virtual void Construct();
	virtual void Destruct();

protected:
	virtual void OnEnter();
	virtual void OnLeave();
	virtual void DoUpdate();
};
