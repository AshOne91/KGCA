#pragma once
#include "GameCore.h"
#include "Component.h"
#include "Writer.h"
#include <unordered_map>

class TextInfo
{
public:
	int x = 0;
	int y = 0;
	std::wstring text = L"default";
	D2D1_COLOR_F color = { 1, 1, 1, 1 };
};

class TextManager : public Singleton<TextManager>, public ComponentObject
{
	static unsigned __int64 _AllocIndex;
private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	IDXGISwapChain* _pSwapChain = nullptr;
	std::unordered_map<unsigned __int64, std::pair<TextInfo*, Writer*>> _textDrawList;

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
	unsigned __int64 CreateText(std::wstring& font, int x, int y, int size, D2D1_COLOR_F color);
	void DestroyText(unsigned __int64 index);
	void SetText(unsigned __int64 index, std::wstring& text, D2D1_COLOR_F color = {1.0f, 1.0f, 1.0f, 1.0f});

public:
	TextManager();
	virtual ~TextManager();
};

#define I_TextManager TextManager::GetInstance()