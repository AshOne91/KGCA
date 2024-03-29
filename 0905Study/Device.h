#pragma once
#include "WIndow.h"
class Device : public Window
{
public:
	// �������̽�-> �ϵ���� ���� ���� -> ȹ��
	ID3D11Device* _pd3dDevice = nullptr; // ����̽� ��ü
	ID3D11DeviceContext* _pImmediateContext = nullptr; // ����̽� ���ؽ�Ʈ ��ü
	IDXGIFactory* _pGIFactory = nullptr; 
	IDXGISwapChain* _pSwapChain = nullptr; //����ü�� ��ü
	ID3D11RenderTargetView* _pRTV = nullptr; // ���� ����Ÿ�� ��
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
