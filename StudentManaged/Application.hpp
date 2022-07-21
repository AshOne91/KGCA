#include "Application.h"

template <typename T>
Application<T>::Application()
{
	_activeSceneController._first = nullptr;
	_activeSceneController._second = nullptr;
}

template <typename T>
Application<T>::~Application()
{
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
	Application<T>::Destruct();
}

template <typename T>
void Application<T>::OnApplicationQuit()
{
	OnDeinit();
}

template <typename T>
void Application<T>::Update()
{
	DoUpdate();
}

template <typename T>
void Application<T>::LoadScene(std::string sceneName)
{

}

template <typename T>
template <typename U, class _SceneController, class _SceneControllerInterface>
void Application<T>::CreateScene()
{
	if (_activeSceneController._first != nullptr)
	{
		_activeSceneController._first.OnDisable();
		_activeSceneController._first = nullptr;
		_activeSceneController._second = nullptr;
	}
	_SceneController::Instance()->OnEnable();
}

template <typename T>
template <typename U, class _AppSubSystem, class _UpdatableInterface>
void Application<T>::CreateAppSubSystem()
{
	if (_activeSceneController._first != nullptr)
	{
		_activeSceneController._first.OnDisable();
		_activeSceneController._first = nullptr;
		_activeSceneController._second = nullptr;
	}
}

template <typename T>
std::string Application<T>::GetApplicationName()
{
	return this->_applicationName;
}