#pragma once
#include "SceneController.h"
#include "enum.h"

class SceneFind : public SceneController<SceneFind>
{
public:
	SceneFind();
	virtual ~SceneFind();

public:
	virtual void Construct();
	virtual void Destruct();

protected:
	virtual void OnEnter();
	virtual void OnLeave();
	virtual void DoUpdate();
};