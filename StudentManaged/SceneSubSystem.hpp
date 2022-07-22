#include "SceneSubSystem.h"

template <typename T>
std::string SceneSubSystem<T>::GetSceneControllerName() const
{
	return _sceneControllerName;
}

template <typename T>
void SceneSubSystem<T>::OnSetParentName(const std::string& sceneControllerName)
{
	_sceneControllerName = sceneControllerName;
}

template <typename T>
void SceneSubSystem<T>::OnEnalbe()
{
	Singleton<T>::OnEnable();
}

template <typename T>
void SceneSubSystem<T>::OnDisable()
{
	Singleton<T>::OnDisable();
}

template <typename T>
void SceneSubSystem<T>::Construct()
{
	Singleton<T>::Construct();
}

template <typename T>
void SceneSubSystem<T>::Destruct()
{
	Singleton<T>::Destruct();
}