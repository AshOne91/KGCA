#pragma once
#include "State.h"
#include "ObjectManager.h"
#include "TextManager.h"
#include "UIManager.h"
#include <unordered_map>

class ComponentObject;
class Scene : public State
{
	
private:
	std::unordered_map<unsigned __int64, ComponentObject*> _objectList;
	std::set<unsigned __int64> _textList;
	std::set<unsigned __int64> _uiList;

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

	void AddObject(ComponentObject* pObj)
	{
		_objectList.insert({ pObj->GetIndex(), pObj });
	}

	void RemoveObject(unsigned __int64 iIndex)
	{
		_objectList.erase(iIndex);
	}

	unsigned __int64 CreateText(std::wstring font, int x, int y, int size, D2D1_COLOR_F color = { 0.0f, 0.0f, 0.0f, 1.0f })
	{
		unsigned __int64 index = I_TextManager.CreateText(font, x, y, size, color);
		_textList.insert(index);
		return index;
	}

	void SetText(unsigned __int64 index, std::wstring text, D2D1_COLOR_F color = { 0.0f, 0.0f, 0.0f, 1.0f })
	{
		I_TextManager.SetText(index, text, color);
	}

	void DestroyText(unsigned __int64 index)
	{
		_textList.erase(index);
		I_TextManager.DestroyText(index);
	}

	template<typename T>
	T* CreateUI()
	{
		T* pNewUI = I_UIManager.CreateUI<T>();
		_uiList.insert(pNewUI->GetIndex());
		return pNewUI;
	}

	void DestroyUI(unsigned __int64 iIndex)
	{
		_uiList.erase(iIndex);
		I_UIManager.DestroyObject(iIndex);
	}

	Scene() = default;
	virtual ~Scene() = default;
};

