#pragma once
#include <string>
#include <list>
#include "Singleton.h"
#include "SceneSubSystem.h"

template <typename T>
class SceneController abstract : public Singleton<T>, public SceneControllerInterface
{
private:
	std::string _applicationName;
	std::string _sceneName;
	LinkedList<Pair<BaseObject*, UpdatableInterface*>> _sceneSubSystems;

public:
	SceneController() = default;
	virtual ~SceneController() = default;

public:
	virtual void Construct();
	virtual void Destruct();

protected:
	//subSystem 생성 후 Construct 호출 안함
	template <typename U>
	U CreateSceneSubSystem();

public:
	void DoUpdateManaged();
	virtual void OnEnable();
	virtual void OnDisable();

protected:
	virtual void OnEnter() = 0;
	virtual void OnLeave() = 0;
	virtual void DoUpdate() = 0;

public:
	virtual void OnSetApplicationName(const std::string& applicationName);

public:
	std::string GetSceneName();

public:
	virtual bool OnMessage(BaseObject* sender, const std::string& message);
};

#include "SceneController.hpp"

