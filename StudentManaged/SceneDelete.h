#pragma once
#include "SceneController.h"
#include "enum.h"

class SceneDelete : public SceneController<SceneDelete>
{
public:
	SceneDelete();
	virtual ~SceneDelete();

public:
	virtual void Construct();
	virtual void Destruct();

protected:
	virtual void OnEnter();
	virtual void OnLeave();
	virtual void DoUpdate();
};