#include "SceneController.h"
#include "TokenSplit.h"

template <typename T>
void SceneController<T>::Construct()
{
	Singleton<T>::Construct();
	for(auto iter = _sceneSubSystems.begin(); iter != _sceneSubSystems.end(); ++iter)
	{
		BaseObject* pSceneSubSystem = (*iter)._first;
		UpdatableInterface* pUpdatable = (*iter)._second;
		pSceneSubSystem->Construct();
		pUpdatable->OnSetParentName(_sceneName);
	}
}

template <typename T>
void SceneController<T>::Destruct()
{
	for (auto iter = _sceneSubSystems.begin(); iter != _sceneSubSystems.end(); ++iter)
	{
		BaseObject* pSceneSubSystem = (*iter)._first;
		pSceneSubSystem->Destruct();
	}
	_sceneSubSystems.clear();
	Singleton<T>::Destruct();
}

template <typename T>
template <typename U>
U SceneController<T>::CreateSceneSubSystem()
{
	U* newSceneSubSystem = (U::Instance());
	Pair<BaseObject*, UpdatableInterface*> newSubSystem;
	newSubSystem._first = newSceneSubSystem;
	newSubSystem._second = newSceneSubSystem;
	_sceneSubSystems.push_back(newSubSystem);
}

template <typename T>
void SceneController<T>::DoUpdateManaged()
{
	for (auto iter = _sceneSubSystems.begin(); iter != _sceneSubSystems.end(); ++iter)
	{
		UpdatableInterface* update = (*iter)._second;
		update->DoUpdate();
	}
	DoUpdate();
}

template <typename T>
void SceneController<T>::OnEnable()
{
	OnEnter();
}

template <typename T>
void SceneController<T>::OnDisable()
{
	OnLeave();
}

template <typename T>
void SceneController<T>::OnSetApplicationName(const std::string& applicationName)
{
	_applicationName = applicationName;
}

template <typename T>
std::string SceneController<T>::GetSceneName()
{
	return _sceneName;
}

template <typename T>
bool SceneController<T>::OnMessage(BaseObject* sender, const std::string& message)
{
	LinkedList<std::string> onMessage;
	std::string process;
	std::string param;
	Split(message, ":", onMessage);
	if (onMessage.size() == 2)
	{
		process = (*onMessage.begin());
		param = (*(++onMessage.begin()));
	}

	if (process == "OnSetApplicationName")
	{
		OnSetApplicationName(param);
		return true;
	}

	for (auto iter = _sceneSubSystems.begin(); iter != _sceneSubSystems.end(); ++iter)
	{
		if (iter->_first->OnMessage(sender, message) == true)
		{
			return true;
		}
	}
	return false;
}