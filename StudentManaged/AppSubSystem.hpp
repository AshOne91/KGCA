#include "AppSubSystem.h"

template <typename T>
void AppSubSystem<T>::OnSetParentName(const std::string& name)
{
	_gameApplicationName = name;
}

template <typename T>
void AppSubSystem<T>::OnEnable()
{
	Singleton<T>::OnEnable();
}

template <typename T>
void AppSubSystem<T>::OnDisable()
{
	Singleton<T>::OnDisable();
}

template <typename T>
void AppSubSystem<T>::Construct()
{
	Singleton<T>::Construct();
}

template <typename T>
void AppSubSystem<T>::Destruct()
{
	Singleton<T>::Destruct();
}