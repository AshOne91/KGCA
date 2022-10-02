#pragma once
#include "GameCore.h"
#include "enum.h"
#include "Component.h"
#include <unordered_map>

class EventManager : public Singleton<EventManager>, public ComponentObject
{
private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

private:
	friend class Singleton<EventManager>;

private:
	std::unordered_map<EventType, std::unordered_map<unsigned __int64, ComponentObject*>> _ListenerList;

public:
	void Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;

public:
	void AddListener(EventType eventType, ComponentObject* pComponent);
	void PostNotifycation(EventType eventType, NotifyType notifyType, ComponentObject* pSender, Message* message);
	void RemoveEvent(EventType eventType);
	void RemoveComponentObject(ComponentObject* pComponent);

public:
	EventManager();
	~EventManager();
};

#define I_EventManager EventManager::GetInstance()
