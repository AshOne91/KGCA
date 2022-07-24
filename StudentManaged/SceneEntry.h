#pragma once
#include  "SceneController.h"

class SceneEntry : public SceneController<SceneEntry>
{
private:
	std::string _entryLogo;

public:
	SceneEntry();
	virtual ~SceneEntry();

public:
	virtual void Construct();
	virtual void Destruct();

protected:
	virtual void OnEnter();
	virtual void OnLeave();
	virtual void DoUpdate();
};
