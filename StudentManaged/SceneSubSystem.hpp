#include "SceneSubSystem.h"

template <typename T>
SceneSubSystem<T>::SceneSubSystem()
{
}

template <typename T>
SceneSubSystem<T>::~SceneSubSystem()
{
}

template <typename T>
std::string SceneSubSystem<T>::GetSceneControllerName() const
{
	return _sceneControllerName;
}

template <typename T>
void SceneSubSystem<T>::OnSetSceneController(const std::string& sceneControllerName)
{
	_sceneControllerName = sceneControllerName;
}