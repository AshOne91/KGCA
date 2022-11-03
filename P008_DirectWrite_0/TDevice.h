#pragma once
#include "TDefine.h"

class TDevice
{
public:
	//--------------------------------------------------------------------------------------
	// Global Variables
	//--------------------------------------------------------------------------------------	
	ID3D11Device*           m_pd3dDevice;		// ����̽� ��ü
	IDXGISwapChain*         m_pSwapChain;		// ����ü�� ��ü
	ID3D11RenderTargetView* m_pRenderTargetView;// ���� ����Ÿ�� ��
	D3D11_VIEWPORT			m_ViewPort;			// ����Ʈ 
	D3D_DRIVER_TYPE         m_driverType;		// ����̽� Ÿ��( ����Ʈ:�ϵ���� ���� )
	IDXGIFactory*			m_pGIFactory;		// DXGI ��ü
	ID3D11DeviceContext*    m_pImmediateContext; // ����̽� ���ؽ�Ʈ
	D3D_FEATURE_LEVEL       m_FeatureLevel;		 // Ư������
	BOOL					m_IsFullScreenMode;	// Ǯ��ũ�� ����̽� �����Ǵ�
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
	// ����̽� �� ����ü�� ���� : InitDevice()
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
	// ����� Ŭ���̾�Ʈ ������ �缳���Ѵ�.
	//--------------------------------------------------------------------------------------
	virtual		HRESULT		ResizeDevice(UINT iWidth, UINT iHeight);
	virtual		HRESULT		DeleteDxResource();
	virtual		HRESULT		CreateDxResource();
public:
	TDevice(void);
	virtual ~TDevice(void);
};
