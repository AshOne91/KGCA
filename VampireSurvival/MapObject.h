#pragma once
#include "Object2D.h"
#include "Spawner.h"

enum class MapRotateType
{
	Up = 0,
	Right,
	Down,
	Left
};

class MapObject : public Object2D
{
private:
	Spawner* _pSpawner = nullptr;

public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	virtual void UpdateVertexBuffer() override;
};

