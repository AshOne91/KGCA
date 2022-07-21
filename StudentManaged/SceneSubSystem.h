#pragma once
#include<string>
#include "Singleton.h"
#include "Interface.h"

template <typename T>
class SceneSubSystem abstract : public Singleton<T>, public UpdatableInterface<T>
{
private:
	std::string _sceneControllerName;

public:
	SceneSubSystem();
	virtual ~SceneSubSystem();

public:
	virtual void DoUpdate() = 0;

public:
	std::string GetSceneControllerName() const;
	void OnSetSceneController(const std::string& sceneControllerName);
};

#include "SceneSubSystem.hpp"

