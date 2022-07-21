#pragma once

template <typename T>
class SceneControllerInterface abstract
{
	virtual void DoUpdateManaged() = 0;
};

template <typename T>
class UpdatableInterface abstract
{
	virtual void DoUpdate() = 0;
};