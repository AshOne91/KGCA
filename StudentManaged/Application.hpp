#include "Application.h"

template <typename T>
std::string Application<T>::GetApplicationName()
{
	return this->_applicationName;
}