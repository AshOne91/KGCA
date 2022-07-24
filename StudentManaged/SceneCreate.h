#pragma once
#include "SceneController.h"
#include "enum.h"

class Subject;
class SceneCreate : public SceneController<SceneCreate>
{
public:
	SceneCreate();
	virtual ~SceneCreate();

public: 
	Subject* CreateSubject(ESubjectType type);

public:
	virtual void Construct();
	virtual void Destruct();

protected:
	virtual void OnEnter();
	virtual void OnLeave();
	virtual void DoUpdate();
};