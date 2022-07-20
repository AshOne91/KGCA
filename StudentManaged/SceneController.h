#pragma once
#include <string>
#include "Singleton.h"

class SceneControllerInterface
{
	virtual void Update_Managed() = 0;
};

template <typename T>
class SceneController : Singleton<T>
{
private:
	std::string _sceneName;



public:
	std::string GetSceneName();
};

#include "Singleton.hpp"

