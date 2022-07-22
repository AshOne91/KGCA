#include "Singleton.h"

template <typename T> T* Singleton<T>::_instance = nullptr;

template <typename T>
T* Singleton<T>::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new T();
	}
	return _instance;
}

template <typename T>
void  Singleton<T>::DestroyInstance()
{
	if (_instance != nullptr)
	{
		delete _instance;
		_instance = nullptr;
	}
}

template <typename T>
void Singleton<T>::OnEnable()
{
	BaseObject::OnEnable();
}

template <typename T>
void Singleton<T>::OnDisable()
{
	BaseObject::OnDisable();
}

template <typename T>
void Singleton<T>::Construct()
{
	BaseObject::Construct();
}

template <typename T>
void Singleton<T>::Destruct()
{
	BaseObject::Destruct();
}