#pragma once
#include "enum.h"
#include <list>
#include <unordered_map>

class Message;
class ComponentObject abstract
{
private:
	static unsigned __int64 s_uiAllocIndex;

private:
	unsigned __int64 _uiIndex = 0;
	std::unordered_map<size_t, ComponentObject*> _componentList;

public:
	unsigned __int64 GetIndex();

public:
	ComponentObject();
	~ComponentObject();

public:
	template<typename T>
	void CreateComponent()
	{
		T* pComponent = new T();
		_componentList.insert({ typeid(T).hash_code(), pComponent });
		pComponent->CInit();
	}

	template<typename T>
	void AddComponent(T* pComponent)
	{
		_componentList.insert({ typeid(T).hash_code(), pComponent });
	}

	template<typename T>
	T* GetComponent()
	{
		auto iter = _componentList.find(typeid(T).hash_code());
		if (iter != _componentList.end())
		{
			return nullptr;
		}
		return iter->second;
	}

	virtual bool CInit();
	virtual bool CFrame();
	virtual bool CRender();
	virtual bool CRelease();
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg);
};
