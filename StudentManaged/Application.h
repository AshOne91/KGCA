#pragma once
#include <string>
#include "Pair.h"
#include "SceneController.h"
#include "SceneSubSystem.h"
#include "AppSubSystem.h"
#include "Interface.h"
#include "Singleton.h"
#include "LinkedList.h"

template <typename T>
class Application abstract : public Singleton<T>
{
private:
	std::string _applicationName;

	template <typename U, class _AppSubSystem = AppSubSystem<U>, class _UpdatableInterface = UpdatableInterface<U>>
	LinkedList<Pair<_AppSubSystem*, _UpdatableInterface*>> _appSubSystem;
	template <typename U, class _SceneController = SceneController<U>, class _SceneControllerInterface = SceneControllerInterface<U>>
	Pair<_SceneController*, _SceneControllerInterface*> _activeSceneController;


public:
	Application();
	virtual ~Application();

public:
	virtual void Construct();
	virtual void Destruct();

public:
	void Update();
	void LoadScene(std::string sceneName/*포인터로 변경*/);

	template <typename U, class _SceneController = SceneController<U>, class _SceneControllerInterface = SceneControllerInterface<U>>
	void CreateScene();

protected:
	template <typename U, class _AppSubSystem = AppSubSystem<U>, class _UpdatableInterface = UpdatableInterface<U>>
	void CreateAppSubSystem();

private:
	void OnApplicationQuit();

	template <typename U, class _SceneController = SceneController<U>, class _SceneControllerInterface = SceneControllerInterface<U>>
	void OnActivatedSceneController(_SceneController*, _SceneControllerInterface*);

protected:
	virtual void OnInit() = 0;
	virtual void OnDeinit() = 0;
	virtual void DoUpdate() = 0;

public:
	std::string GetApplicationName();
};

#include "Application.hpp"