#pragma once
#include "GameCore.h"
#include "Component.h"
#include "Writer.h"

class TextManager : public Singleton<TextManager>, public ComponentObject
{
	static unsigned __int64 _AllocIndex;
private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	IDXGISwapChain* _pSwapChain = nullptr;

private:
	friend class Singleton<TextManager>;

public:
	void Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, IDXGISwapChain* pSwapChain);

public:
	virtual bool CInit() override;
	virtual bool CFrame() override;
	virtual bool CRender() override;
	virtual bool CRelease() override;
	virtual bool OnEvent(EventType eventType, ComponentObject* pSender, Message* msg) override;

public:
	TextManager();
	virtual ~TextManager();
};

#define I_TextManager TextManager::GetInstance()