#pragma once
#include "WIndow.h"
class Device : public Window
{
public:
	// 인터페이스-> 하드웨어 직접 제어 -> 획득
	ID3D11Device* _pd3dDevice = nullptr; // 디바이스 객체
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	IDXGIFactory* _pGIFactory = nullptr;
	IDXGISwapChain* _pSwapChain = nullptr;
	ID3D11RenderTargetView* _pRTV = nullptr;
public:
	HRESULT CreateDevice();
	HRESULT CreateDXGIDevice();
	HRESULT CreateSwapChain();
	HRESULT CreateRenderTargetView();
	void CreateViewport();
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
private:
	bool CoreInit() override;
	bool CoreFrame() override;
	bool CorePreRender();
	bool CoreRender() override;
	bool CorePostRender();
	bool CoreRelease() override;

};
