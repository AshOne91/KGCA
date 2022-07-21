#include "Singleton.h"

template <typename T> T* Singleton<T>::_instance = nullptr;

template <typename T>
Singleton<T>::Singleton()
{

}

template <typename T>
Singleton<T>::~Singleton()
{
}


template <typename T>
T* Singleton<T>::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new T();
		_instance->Awake();
	}
	return _instance;
}

template <typename T>
void  Singleton<T>::DestroyInstance()
{
	if (_instance != nullptr)
	{
		_instance->OnDestroy();
		delete _instance;
		_instance = nullptr;
	}
}

template <typename T>
void Singleton<T>::Construct()
{

}

template <typename T>
void Singleton<T>::Destruct()
{

}