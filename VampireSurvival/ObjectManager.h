#pragma once
#include "GameCore.h"
#include "Component.h"
#include "EventManager.h"
#include "Message.h"

class ObjectManager : public Singleton<ObjectManager>, public ComponentObject
{
private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

private:
	friend class Singleton<ObjectManager>;
	std::map<unsigned __int64, ComponentObject*> _objectList;

public:
	void Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;

public:
	template<typename T>
	T* CreateObject()
	{
		T* pData = new T();
		_objectList.insert({ pData->GetIndex(), pData });
		pData->CInit();

		Message msg;
		msg.eventType = EventType::CreateObject;
		msg._uiSender = GetIndex();
		msg._uiReceiver = 0;
		msg._pExtraInfo = nullptr;
		I_EventManager.PostNotifycation(EventType::CreateObject, NotifyType::BroadCast, this, &msg);
		return pData;
	}
	void DestroyObject(unsigned __int64 iIndex);
	template<typename T>
	T* GetObject(unsigned __int64 iIndex)
	{
		auto iter = _objectList.find(iIndex);
		if (iter == _objectList.end())
		{
			return nullptr;
		}
		return dynamic_cast<T*>(iter->second);
	}

private:
	ObjectManager();
public:
	~ObjectManager();
};

#define I_ObjectManager ObjectManager::GetInstance() 

