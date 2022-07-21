#pragma once
#include <string>
#include "Singleton.h"
#include "SceneSubSystem.h"
#include "LinkedList.h"
#include "Pair.h"

template <typename T>
class SceneController abstract : public Singleton<T>, public SceneControllerInterface<T>
{
private:
	std::string _sceneName;

	template <typename U, class _SceneSubSystem = SceneSubSystem<U>, class _UpdatableInterface = UpdatableInterface<U>>
	LinkedList<Pair<_SceneSubSystem*, _UpdatableInterface*>> _sceneSubSystems;

public:
	SceneController();
	virtual ~SceneController();

public:
	template <typename U, class _SceneSubSystem = SceneSubSystem<U>, class _UpdatableInterface = UpdatableInterface<U>>
	void Construct() override;
	template <typename U, class _SceneSubSystem = SceneSubSystem<U>, class _UpdatableInterface = UpdatableInterface<U>>
	void Destruct() override;



protected:
	template <typename U, class _SceneSubSystem = SceneSubSystem<U>, class _UpdatableInterface = UpdatableInterface<U>>
	void AddUpdatableInterface(_SceneSubSystem* sceneSubSystem);

	template <typename U, class _SceneSubSystem = SceneSubSystem<U>, class _UpdatableInterface = UpdatableInterface<U>>
	void RemoveUpdatableInterface(_SceneSubSystem* sceneSubSystem);

	template <typename U, class _SceneSubSystem = SceneSubSystem<U>, class _UpdatableInterface = UpdatableInterface<U>>
	_SceneSubSystem CreateSceneSubSystem();

private:
	void OnEnterManaged();
public:
	template <typename U, class _SceneSubSystem = SceneSubSystem<U>, class _UpdatableInterface = UpdatableInterface<U>>
	void DoUpdateManaged();
	void OnEnable();
	void OnDisable();

protected:
	virtual void OnEnter() = 0;
	virtual void OnLeave() = 0;
	virtual void DoUpdate() = 0;

public:
	std::string GetSceneName();
};

#include "SceneController.hpp"

