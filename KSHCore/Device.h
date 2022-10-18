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
	// �������̽�-> �ϵ���� ���� ���� -> ȹ��
	ComPtr<ID3D11Device> _pd3dDevice = nullptr; // ����̽� ��ü
	ComPtr<ID3D11DeviceContext> _pImmediateContext = nullptr; // ����̽� ���ؽ�Ʈ ��ü
	ComPtr<IDXGIFactory> _pGIFactory = nullptr;

	ComPtr<IDXGISwapChain> _pSwapChain = nullptr; //����ü�� ��ü
	ComPtr<ID3D11RenderTargetView> _pRTV = nullptr; // ���� ����Ÿ�� ��
	ComPtr<ID3D11DepthStencilView> _pDepthStencilView = nullptr; // ���� ���Ľ� ��
	D3D11_VIEWPORT _vp;

public:
	//����̽� ����
	HRESULT CreateDevice();
	//���丮 ����
	HRESULT CreateDXGIDevice();
	//����ü�� ����
	HRESULT CreateSwapChain();
	// ����Ÿ�Ϻ� ����
	HRESULT CreateRenderTargetView();
	// ���� ���Ľ� �� ����
	HRESULT CreateDepthStencilView();
	// ����Ʈ ����
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
