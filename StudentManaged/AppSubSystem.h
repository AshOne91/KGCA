#pragma once
#include <string>
#include "Singleton.h"
#include "Interface.h"

template <typename T>
class AppSubSystem abstract : public Singleton<T>, public UpdatableInterface
{
private:
	std::string _gameApplicationName;

public:
	virtual void DoUpdate() = 0;

public:
	virtual void OnEnable();
	virtual void OnDisable();

public:
	virtual void Construct();
	virtual void Destruct();

public:
	virtual void OnSetParentName(const std::string& name);

public:
	virtual bool OnMessage(BaseObject* sender, const std::string& message) = 0;
};

#include "AppSubSystem.hpp"