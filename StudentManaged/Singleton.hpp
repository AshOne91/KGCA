#include "Singleton.h"

template<typename T>
T* Singleton<T>::Instance()
{
	static T s_Instance;
	return &s_Instance;
}