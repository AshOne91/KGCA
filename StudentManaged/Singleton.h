#pragma once
#include "BaseObject.h"

template <typename T>
class Singleton abstract : public BaseObject
{
private:
	static T* _instance;

public:
	static T* Instance();
	static void DestroyInstance();

public:
	Singleton() = default;
	virtual ~Singleton();

public:
	virtual void OnEnable();
	virtual void OnDisable();

public:
	virtual void Construct();
	virtual void Destruct();

public:
	virtual bool OnMessage(BaseObject* sender, const std::string& message) = 0;
};

#include "Singleton.hpp"
