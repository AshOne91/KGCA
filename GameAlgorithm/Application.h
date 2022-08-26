#pragma once
#include <string>
#include <list>
#include "SceneController.h"
#include "SceneSubSystem.h"
#include "AppSubSystem.h"
#include "Interface.h"
#include "Singleton.h"

class BaseObject;
template <typename T>
class Application abstract : public Singleton<T>
{
private:
	std::string _applicationName;
	
	std::list<std::pair<BaseObject*, UpdatableInterface*>> _appSubSystem;
	std::list<std::pair<BaseObject*, SceneControllerInterface*>> _sceneController;
	std::pair<BaseObject*, SceneControllerInterface*> _activeSceneController;

public:
	Application(std::string applicationName);
	virtual ~Application();

public:
	virtual void OnEnable();
	virtual void OnDisable();

public:
	virtual void Construct();
	virtual void Destruct();

public:
	void Update();
	template <typename U>
	void LoadScene();

	template <typename U>
	void CreateScene();

protected:
	template <typename U>
	void CreateAppSubSystem();

public:
	void OnApplicationQuit();

protected:
	virtual void OnInit() = 0;
	virtual void OnDeinit() = 0;
	virtual void DoUpdate() = 0;

public:
	std::string GetApplicationName();

public:
	virtual bool OnMessage(BaseObject* sender, const std::string& message);
};

#include "Application.hpp"