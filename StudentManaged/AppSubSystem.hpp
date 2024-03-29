#include "AppSubSystem.h"
#include "TokenSplit.h"
#include "LinkedList.h"

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

template <typename T>
bool AppSubSystem<T>::OnMessage(BaseObject* sender, const std::string& message)
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

	if (process == "OnSetParentName")
	{
		OnSetParentName(param);
		return true;
	}
	return false;
}