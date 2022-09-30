#pragma once
#include "GameCore.h"
#include "Component.h"

class CollisionManager : public Singleton<CollisionManager>, public ComponentObject
{
private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

private:
	friend class Singleton<CollisionManager>;

public:
	void Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;

private:
	CollisionManager();
public:
	~CollisionManager();
};

#define I_CollisionManager CollisionManager::GetInstance()
