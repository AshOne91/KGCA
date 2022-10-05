#pragma once
#include "GameCore.h"
#include "Component.h"
#include "FrameSkip.h"
#include <unordered_map>
#include <set>

class CircleComponent;
class CollisionManager : public Singleton<CollisionManager>, public ComponentObject
{
private:
	FrameSkip _frameSkip;
	float _fCollisionCheckRadious = 0.0f;
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	std::unordered_map<unsigned __int64, std::unordered_map<ComponentObject*, CircleComponent*>> _circleComponentList;
	std::unordered_map<CircleComponent*, std::set<CircleComponent*>> _collisionCheckList;

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

public:
	CollisionManager();
	~CollisionManager();
};

#define I_CollisionManager CollisionManager::GetInstance()
