#include "SceneController.h"

template <typename T>
SceneController<T>::SceneController()
{
}

template <typename T>
SceneController<T>::~SceneController()
{
}

template <typename T>
template <typename U, class _SceneSubSystem, class _UpdatableInterface>
void SceneController<T>::Construct()
{
	Singleton<T>::Construct();
	for(auto iter = _sceneSubSystems.begin(); iter != _sceneSubSystems.end(); ++iter)
	{
		_SceneSubSystem* pSceneSubSystem = (*iter)._first;
		pSceneSubSystem->OnSetSceneController(_sceneName);
	}
}

template <typename T>
template <typename U, class _SceneSubSystem, class _UpdatableInterface>
void SceneController<T>::Destruct()
{
	for (auto iter = _sceneSubSystems.begin(); iter != _sceneSubSystems.end(); ++iter)
	{
		_SceneSubSystem* pSceneSubSystem = (*iter)._first;
		pSceneSubSystem->Destruct();
	}
	_sceneSubSystems.clear();
	Singleton<T>::Destruct();
}

template <typename T>
template <typename U, class _SceneSubSystem, class _UpdatableInterface>
void SceneController<T>::AddUpdatableInterface(_SceneSubSystem* sceneSubSystem)
{
	Pair<_SceneSubSystem*, _UpdatableInterface*> newSystem;
	newSystem._first = sceneSubSystem;
	newSystem._second = sceneSubSystem;
	sceneSubSystem.OnSetSceneController(_sceneControllerName);
	_sceneSubSystems.push_back(newSystem);
}

template <typename T>
template <typename U, class _SceneSubSystem, class _UpdatableInterface>
void SceneController<T>::RemoveUpdatableInterface(_SceneSubSystem* sceneSubSystem)
{
	for (auto iter = _sceneSubSystems.begin(); iter != _sceneSubSystems.end(); ++iter)
	{
		_SceneSubSystem* system = (*iter)._first;
		if (system == sceneSubSystem)
		{
			_sceneSubSystems.erase(iter);
			break;
		}
	}
}

template <typename T>
template <typename U, class _SceneSubSystem, class _UpdatableInterface>
_SceneSubSystem SceneController<T>::CreateSceneSubSystem()
{
	U* newSceneSubSystem = &(U::Instance());
	Pair<_SceneSubSystem*, _UpdatableInterface*> newSystem;
	newSystem._first = newSceneSubSystem;
	newSystem._second = newScenSubSystem;
	newSceneSubSystem.OnSetSceneController(_sceneControllerName);
	_sceneSubSystems.push_back(newSystem);
}

template <typename T>
void SceneController<T>::OnEnterManaged()
{
	OnEnter();
	//UTGameApplicationProxy._Instance.InvokeOnActivatedSceneController_Managed(this.gameObject, this as UTSceneControllerInterface);
}

template <typename T>
template <typename U, class _SceneSubSystem, class _UpdatableInterface>
void SceneController<T>::DoUpdateManaged()
{
	for (auto iter = _sceneSubSystems.begin(); iter != _sceneSubSystems.end(); ++iter)
	{
		_UpdatableInterface* update = (*iter)._second;
		update->DoUpdate();
	}
	DoUpdate();
}

template <typename T>
void SceneController<T>::OnEnable()
{
	OnEnterManaged()
}

template <typename T>
void SceneController<T>::OnDisable()
{
	OnLeave();
}

template <typename T>
std::string SceneController<T>::GetSceneName()
{
	return _sceneName;
}