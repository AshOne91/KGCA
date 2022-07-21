#include "AppSubSystem.h"

template <typename T>
void AppSubSystem<T>::OnSetGamePllication(const std::string& gameApplicationName)
{
	_gameApplicationName = gameApplicationName;
}