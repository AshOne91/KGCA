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
	ComPtr<ID3D11DepthStencilView> _pDepthStencilView = nullptr; // 깊이 스탠실 뷰
	D3D11_VIEWPORT _vp;

public:
	//디바이스 생성
	HRESULT CreateDevice();
	//팩토리 생성
	HRESULT CreateDXGIDevice();
	//스왑체인 생성
	HRESULT CreateSwapChain();
	// 랜더타켓뷰 생성
	HRESULT CreateRenderTargetView();
	// 깊이 스탠실 뷰 생성
	HRESULT CreateDepthStencilView();
	// 뷰포트 설정
	void CreateViewport();
	virtual HRESULT ResizeDevice(UINT width, UINT height);

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual HRESULT CreateDXResource();
	virtual HRESULT DeleteDXResource();
};
