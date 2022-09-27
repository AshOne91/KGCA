#pragma once
#include "WIndow.h"
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")

class Device : public Window
{
public:
	// 인터페이스-> 하드웨어 직접 제어 -> 획득
	ComPtr<ID3D11Device> _pd3dDevice = nullptr; // 디바이스 객체
	ComPtr<ID3D11DeviceContext> _pImmediateContext = nullptr; // 디바이스 컨텍스트 객체
	ComPtr<IDXGIFactory> _pGIFactory = nullptr;
	ComPtr<IDXGISwapChain> _pSwapChain = nullptr; //스왑체인 객체
	ComPtr<ID3D11RenderTargetView> _pRTV = nullptr; // 메인 랜더타겟 뷰
	D3D11_VIEWPORT _vp;

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
