#pragma once
#include "TWindow.h"

class TDevice : public TWindow
{
public:
	// window runtime c++ template library(wrl)
	ComPtr<ID3D11Device> m_pd3dDevice;
	ComPtr<ID3D11DeviceContext> m_pImmediateContext;
	ComPtr<IDXGISwapChain> m_pSwapChain;
	ComPtr<ID3D11RenderTargetView> _pRenderTargetView;
	D3D_FEATURE_LEVEL m_FeatureLevel;
	DXGI_SWAP_CHAIN_DESC m_SwapChainDesc;
	D3D11_VIEWPORT m_ViewPort;

	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
	ComPtr<ID3D11ShaderResourceView> m_pSRV;
	ComPtr<ID3D11ShaderResourceView> m_pDsvSRV;

public:
	HRESULT InitDevice();
	virtual bool CreateDevice();
	virtual bool CreateRenderTargetView();
	virtual bool CreateDepthStencilView();
	virtual bool SetViewport();
	virtual bool CleapupDevice();

public:
	void ResizeDevice(UINT iWidth, UINT iHeight);
	void ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);

public:
	TDevice();
	virtual ~TDevice();
};

