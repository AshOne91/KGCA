#include "Application.h"
#include "BaseObject.h"

template <typename T>
Application<T>::Application(std::string applicationName):_applicationName(applicationName)
{
	_activeSceneController._first = nullptr;
	_activeSceneController._second = nullptr;
}

template <typename T>
Application<T>::~Application()
{
}

template <typename T>
void Application<T>::OnEnable()
{
	Singleton<T>::OnEnable();
	for (auto iter = _appSubSystem.begin(); iter != _appSubSystem.end(); ++iter)
	{
		iter->_first->OnEnable();
	}
	for (auto iter = _sceneController.begin(); iter != _sceneController.end(); ++iter)
	{
		iter->_first->OnDisable();
	}
}

template <typename T>
void Application<T>::OnDisable()
{
	for (auto iter = _appSubSystem.begin(); iter != _appSubSystem.end(); ++iter)
	{
		iter->_first->OnDisable();
	}
	for (auto iter = _sceneController.begin(); iter != _sceneController.end(); ++iter)
	{
		iter->_first->OnDisable();
	}
	Singleton<T>::OnDisable();
}

template <typename T>
void Application<T>::Construct()
{
	Singleton<T>::Construct();
	OnInit();
}

template <typename T>
void Application<T>::Destruct()
{
	Singleton<T>::Destruct();
}

template <typename T>
void Application<T>::OnApplicationQuit()
{
	OnDeinit();
}

template <typename T>
void Application<T>::Update()
{
	for (auto iter = _appSubSystem.begin(); iter != _appSubSystem.end(); ++iter)
	{
		iter->_second->DoUpdate();
	}

	if (_activeSceneController._first != nullptr)
	{
		_activeSceneController._second->DoUpdateManaged();
	}

	DoUpdate();
}

template <typename T>
template <typename U>
void Application<T>::LoadScene()
{
	if (_activeSceneController._first != nullptr)
	{
		_activeSceneController._first->OnDisable();
		_activeSceneController._first = nullptr;
		_activeSceneController._second = nullptr;
	}
	_activeSceneController._first = (U::Instance());
	_activeSceneController._second = (U::Instance());
	_activeSceneController._first->OnEnable();
}

template <typename T>
template <typename U>
void Application<T>::CreateScene()
{
	Pair<BaseObject*, SceneControllerInterface*> newScene;
	newScene._first = (U::Instance());
	newScene._second = (U::Instance());
	_sceneController.push_back(newScene);
}

template <typename T>
template <typename U>
void Application<T>::CreateAppSubSystem()
{
	Pair<BaseObject*, UpdatableInterface*> newSubSystem;
	newSubSystem._first = U::Instance();
	newSubSystem._second = U::Instance();
	_appSubSystem.push_back(newSubSystem);
}

template <typename T>
std::string Application<T>::GetApplicationName()
{
	return this->_applicationName;
}

template <typename T>
bool Application<T>::OnMessage(BaseObject* sender, const std::string& message)
{
	for (auto iter = _appSubSystem.begin(); iter != _appSubSystem.end(); ++iter)
	{
		if (iter->_first->OnMessage(sender, message) == true)
		{
			return true;
		}
	}
	for (auto iter = _sceneController.begin(); iter != _sceneController.end(); ++iter)
	{
		if (iter->_first->OnMessage(sender, message) == true)
		{
			return true;
		}
	}
	return false;
}