#pragma once
#include "TDefine.h"

class TDevice
{
public:
	//--------------------------------------------------------------------------------------
	// Global Variables
	//--------------------------------------------------------------------------------------	
	ID3D11Device*           m_pd3dDevice;		// 디바이스 객체
	IDXGISwapChain*         m_pSwapChain;		// 스왑체인 객체
	ID3D11RenderTargetView* m_pRenderTargetView;// 메인 랜더타켓 뷰
	D3D11_VIEWPORT			m_ViewPort;			// 뷰포트 
	D3D_DRIVER_TYPE         m_driverType;		// 디바이스 타입( 디폴트:하드웨어 가속 )
	IDXGIFactory*			m_pGIFactory;		// DXGI 객체
	ID3D11DeviceContext*    m_pImmediateContext; // 디바이스 컨텍스트
	D3D_FEATURE_LEVEL       m_FeatureLevel;		 // 특성수준
	BOOL					m_IsFullScreenMode;	// 풀스크린 디바이스 여부판단
	DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;
public:

	BOOL					GetFullScreenFlag();
	void					SetFullScreenFlag(BOOL bFlag);
	ID3D11Device*			GetDevice();
	ID3D11DeviceContext*	GetContext();
	IDXGISwapChain*			GetSwapChain();
	ID3D11RenderTargetView*	GetRenderTargetView();
	IDXGIFactory*			GetGIFactory();
public:
	//--------------------------------------------------------------------------------------
	// 디바이스 및 스왑체인 생성 : InitDevice()
	//--------------------------------------------------------------------------------------
	HRESULT		InitDevice(HWND hWnd, UINT iWidth, UINT iHeight, BOOL IsFullScreen = FALSE);
	// 0, InitDevice()
	// 1, CreateGIFactory()
	// 2, CreateDevice()
	// 3, CreateSwapChain()
	// 4, SetRenderTargetView()
	// 5, SetViewPort()
	//--------------------------------------------------------------------------------------
	HRESULT		CreateDevice();
	HRESULT		CreateGIFactory();
	HRESULT		CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeigh, BOOL IsFullScreen = FALSE);
	//--------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------
	HRESULT		SetRenderTargetView();
	HRESULT		SetViewPort();
	bool		CleanupDevice();

	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정한다.
	//--------------------------------------------------------------------------------------
	virtual		HRESULT		ResizeDevice(UINT iWidth, UINT iHeight);
	virtual		HRESULT		DeleteDxResource();
	virtual		HRESULT		CreateDxResource();
public:
	TDevice(void);
	virtual ~TDevice(void);
};
