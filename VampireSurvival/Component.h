#pragma once
#include "enum.h"
#include "Transform.h"
#include "Object.h"
#include <list>
#include <unordered_map>


class Message;
class ComponentObject abstract : public Object
{
private:
	static unsigned __int64 s_uiAllocIndex;

private:
	ComponentObject* _pParent = nullptr;
	unsigned __int64 _uiIndex = 0;
	std::unordered_map<size_t, ComponentObject*> _componentList;

public:
	unsigned __int64 GetIndex();
	Transform _transform;

public:
	ComponentObject();
	virtual ~ComponentObject();

public:
	ComponentObject* GetParentPtr() { return _pParent; }

	template<typename T>
	void CreateComponent()
	{
		T* pComponent = new T();
		_componentList.insert({ typeid(T).hash_code(), pComponent });
		pComponent->_pParent = this;
		pComponent->CInit();
		PostNotify(EventType::CreateComponent, NotifyType::BroadCast, this, pComponent);
	}

	void RemoveComponent()
	{
		for (auto& pair : _componentList)
		{
			delete pair.second;
			pair.second = nullptr;
		}
		_componentList.clear();
	}

	template<typename T>
	void AddComponent(T* pComponent)
	{
		_componentList.insert({ typeid(T).hash_code(), pComponent });
		pComponent->_pParent = this;
		PostNotify(EventType::AddComponent, NotifyType::BroadCast, this, pComponent);
	}

	template<typename T>
	T* GetComponent()
	{
		auto iter = _componentList.find(typeid(T).hash_code());
		if (iter == _componentList.end())
		{
			return nullptr;
		}
		return dynamic_cast<T*>(iter->second);
	}

	template<typename T>
	T* CreateObject()
	{
		T* pComponent = new T();
		PostNotify(EventType::CreateObjectInComponent, NotifyType::BroadCast, this, pComponent);
		return pComponent;
	}

	void DestroyObject(unsigned __int64 uiIndex);

	virtual bool CInit();
	virtual bool CFrame();
	virtual bool CRender();
	virtual bool CRelease();
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg);

private:
	void PostNotify(EventType eventType, NotifyType notiType, ComponentObject* pSender, void* pExtraInfo);
};
