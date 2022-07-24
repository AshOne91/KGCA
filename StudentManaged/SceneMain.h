#pragma once
#include "SceneController.h"
#include "enum.h"

class SceneMain : public SceneController<SceneMain>
{
private:
	std::string _main;
public:
	SceneMain();
	virtual ~SceneMain();

private:
	std::string& DrawMain();

public:
	virtual void Construct();
	virtual void Destruct();

protected:
	virtual void OnEnter();
	virtual void OnLeave();
	virtual void DoUpdate();
};
