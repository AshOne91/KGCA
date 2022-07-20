#pragma once
#include <string>
#include "Singleton.h"

template <typename T>
class Application : public Singleton<T>
{
private:
	std::string _applicationName;

public:
	std::string GetApplicationName();
};

#include "Application.hpp"