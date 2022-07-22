#pragma once

class SceneControllerInterface abstract
{
	virtual void DoUpdateManaged() = 0;
	virtual void OnSetApplicationName(const std::string& name) = 0;
};

class UpdatableInterface abstract
{
	virtual void DoUpdate() = 0;
	virtual void OnSetParentName(const std::string& name) = 0;
};