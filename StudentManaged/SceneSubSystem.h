#pragma once
#include<string>
#include "Singleton.h"
#include "Interface.h"

template <typename T>
class SceneSubSystem abstract : public Singleton<T>, public UpdatableInterface
{
private:
	std::string _sceneControllerName;

public:
	SceneSubSystem() = default;
	virtual ~SceneSubSystem() = default;

public:
	virtual void DoUpdate() = 0;

public:
	virtual void OnEnalbe();
	virtual void OnDisable();

public:
	virtual void Construct();
	virtual void Destruct();

public:
	std::string GetSceneControllerName() const;
	void OnSetParentName(const std::string& sceneControllerName);
};

#include "SceneSubSystem.hpp"

