#include "Device.h"

HRESULT Device::CreateDevice()
{
	// 1) ����̽� ����
	HRESULT hr;
	D3D_FEATURE_LEVEL pFeatureLevel;
	UINT Flags = 0;
	D3D_FEATURE_LEVEL pFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT FeatureLevels = 1;
	hr = D3D11CreateDevice(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, pFeatureLevels, 1, D3D11_SDK_VERSION, &_pd3dDevice, &pFeatureLevel, &_pImmediateContext);
	//pd3dDevice �ٸ� �������̽� ������ ���
	//pImmediateContext ������ �������̽��� ���(����, ����)�� ��
	return hr;
}

HRESULT Device::CreateDXGIDevice()
{
	// 2) ���丮 ����
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&_pGIFactory);
	return hr;
}

HRESULT Device::CreateSwapChain()
{
	// 3) ����ü�� ����
	// �ĸ�(��)���� ���� -> �������
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = _rtClient.right;
	sd.BufferDesc.Height = _rtClient.bottom;
	sd.BufferDesc.Format = DXGI_FORMAT_R10G10B10A2_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = _hWnd;
	sd.Windowed = true;

	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;

	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	return _pGIFactory->CreateSwapChain(_pd3dDevice, &sd, &_pSwapChain);
}

HRESULT Device::CreateRenderTargetView()
{
	// 4) ����Ÿ�ٺ� ����
	HRESULT hr;
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = _pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &_pRTV);
	pBackBuffer->Release();
	return hr;
}

void Device::CreateViewport()
{
	// 5)����Ʈ ����
	D3D11_VIEWPORT vp;
	vp.Width = _rtClient.right;
	vp.Height = _rtClient.bottom;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	_pImmediateContext->RSSetViewports(1, &vp);
}

bool Device::Init()
{
	return false;
}

bool Device::Frame()
{
	return false;
}

bool Device::Render()
{
	return false;
}

bool Device::Release()
{
	return false;
}

bool Device::CoreInit()
{
	HRESULT hr;
	if (FAILED(hr = CreateDXGIDevice()))
	{
		return false;
	}
	if (FAILED(hr = CreateDevice()))
	{
		return false;
	}
	if (FAILED(hr = CreateSwapChain()))
	{
		return false;
	}
	if (FAILED(hr = CreateRenderTargetView()))
	{
		return false;
	}
	CreateViewport();

	return Init();
}

bool Device::CoreFrame()
{

	return Frame();
}

bool Device::CorePreRender()
{
	_pImmediateContext->OMSetRenderTargets(1, &_pRTV, NULL);
	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	_pImmediateContext->ClearRenderTargetView(_pRTV, color);

	return true;
}

bool Device::CoreRender()
{
	CorePreRender();
	Render();
	CorePostRender();
	return true;
}

bool Device::CorePostRender()
{
	_pSwapChain->Present(0, 0);
	return true;
}

bool Device::CoreRelease()
{
	Release();
	if (_pd3dDevice) _pd3dDevice->Release();
	if (_pImmediateContext) _pImmediateContext->Release();
	if (_pGIFactory) _pGIFactory->Release();
	if (_pSwapChain) _pSwapChain->Release();
	if (_pRTV) _pRTV->Release();
	return true;
}
