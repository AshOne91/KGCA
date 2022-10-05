#pragma once
#include "Object2D.h"
#include "Component.h"

class Spawner;
class Monster;
class MapObject : public Object2D, public ComponentObject
{
private:
	Spawner* _pSpawner = nullptr;

public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	virtual void UpdateVertexBuffer() override;

public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;

public:
	void EnableSpawner();
	void DisableSpanwer();
};

