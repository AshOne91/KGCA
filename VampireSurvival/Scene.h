#pragma once
#include "State.h"
#include "ObjectManager.h"
#include <unordered_map>

class ComponentObject;
class Scene : public State
{
	
private:
	std::unordered_map<unsigned __int64, ComponentObject*> _objectList;

protected:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

public:
	virtual void Enter() final;
	virtual void Execute() final;
	virtual void Exit() final;
	void Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

public:
	virtual void OnEnter() = 0;
	virtual void OnExecute() = 0;
	virtual void OnExit() = 0;

public:
	template<typename T>
	T* CreateObject()
	{
		T* pNewObj = I_ObjectManager.CreateObject<T>();
		_objectList.insert({ pNewObj->GetIndex(), pNewObj});
		return pNewObj;
	}

	void DestroyObject(unsigned __int64 iIndex)
	{
		_objectList.erase(iIndex);
		I_ObjectManager.DestroyObject(iIndex);
	}

	template<typename T>
	T* DontDestroyObject()
	{
		return I_ObjectManager.CreateObject<T>();
	}

	Scene() = default;
	virtual ~Scene() = default;
};

