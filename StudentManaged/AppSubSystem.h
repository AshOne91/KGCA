#pragma once
#include <string>
#include "Singleton.h"
#include "Interface.h"

template <typename T>
class AppSubSystem abstract : public Singleton<T>, public UpdatableInterface<T>
{
private:
	std::string _gameApplicationName;

public:
	virtual void DoUpdate() = 0;

public:
	void OnSetGamePllication(const std::string& gameApplicationName);
};

#include "AppSubSystem.hpp"