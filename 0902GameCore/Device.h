#pragma once
#include "WIndow.h"
class Device : public Window
{
public:
	// 인터페이스-> 하드웨어 직접 제어 -> 획득
	ID3D11Device* _pd3dDevice = nullptr; // 디바이스 객체
	ID3D11DeviceContext* _pImmediateContext = nullptr; // 디바이스 컨텍스트 객체
	IDXGIFactory* _pGIFactory = nullptr; 
	IDXGISwapChain* _pSwapChain = nullptr; //스왑체인 객체
	ID3D11RenderTargetView* _pRTV = nullptr; // 메인 랜더타겟 뷰
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
};
