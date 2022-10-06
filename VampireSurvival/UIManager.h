#pragma once
#include "GameCore.h"
#include "Component.h"

class UIManager : public Singleton<UIManager>, public ComponentObject
{
private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	std::map<unsigned __int64, ComponentObject*> _uiList;

private:
	friend class Singleton<UIManager>;

public:
	void Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;

public:
	template <typename T>
	T* CreateUI()
	{
		T* pNewUI = new T();
		_uiList.insert({pNewUI->GetIndex(), pNewUI});
		pNewUI->CInit();
		return pNewUI;
	}

	void DestroyUI(unsigned __int64 iIndex)
	{
		auto iter = _uiList.find(iIndex);
		if (iter == _uiList.end())
		{
			//누가 지운거다.(두번 호출 될 수 있음)
			return;
		}
		iter->second->CRelease();
		delete iter->second;
		_uiList.erase(iIndex);
	}


public:
	UIManager();
	~UIManager();
};

#define I_UIManager UIManager::GetInstance()