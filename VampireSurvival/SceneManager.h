#pragma once
#include "GameCore.h"
#include "Component.h"
#include "StateMachine.h"
#include "Scene.h"

class SceneManager : public Singleton<SceneManager>, public StateMachine<Scene>, public ComponentObject
{
private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

private:
	friend class Singleton<SceneManager>;

public:
	void Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;

public:
	SceneManager();
	~SceneManager();
};

#define I_SceneManager SceneManager::GetInstance()

