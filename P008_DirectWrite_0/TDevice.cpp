#include "TDevice.h"
HRESULT TDevice::CreateDxResource()
{
	return S_OK;
}
HRESULT TDevice::DeleteDxResource()
{
	return S_OK;
}
HRESULT TDevice::InitDevice(HWND hWnd, UINT iWidth, UINT iHeight, BOOL IsFullScreen)
{
	HRESULT hr;
	H_RETURN(CreateDevice());
	H_RETURN(CreateSwapChain(hWnd, iWidth, iHeight, IsFullScreen));
	H_RETURN(SetRenderTargetView());
	H_RETURN(SetViewPort());
	// Alt + Enter 키를 막는다.
	if (FAILED(hr = m_pGIFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER)))
	{
		return hr;
	}
	return hr;
}

BOOL TDevice::GetFullScreenFlag()
{
	return m_IsFullScreenMode;
}
void TDevice::SetFullScreenFlag(BOOL bFlag)
{
	m_IsFullScreenMode = bFlag;
}
ID3D11Device* TDevice::GetDevice()
{
	assert(m_pd3dDevice);
	return m_pd3dDevice;
}
ID3D11DeviceContext* TDevice::GetContext()
{
	assert(m_pImmediateContext);
	return m_pImmediateContext;
}
IDXGISwapChain* TDevice::GetSwapChain()
{
	assert(m_pSwapChain);
	return m_pSwapChain;
}
ID3D11RenderTargetView* TDevice::GetRenderTargetView()
{
	assert(m_pRenderTargetView);
	return m_pRenderTargetView;
}
IDXGIFactory* TDevice::GetGIFactory()
{
	assert(m_pGIFactory);
	return m_pGIFactory;
}
// New
HRESULT TDevice::ResizeDevice(UINT iWidth, UINT iHeight)
{
	if (m_pd3dDevice == NULL) return true;

	HRESULT hr;
	// 바인딩되어 있는 각종 뷰리소스를 해제한다.
	if (FAILED(hr = DeleteDxResource()))
	{
		return hr;
	}
	//--------------------------------------------------------------------------------------
	// 랜더타켓과 깊이스텐실 버퍼를 해제한다.
	//--------------------------------------------------------------------------------------
	m_pImmediateContext->OMSetRenderTargets(0, NULL, NULL);
	if (m_pRenderTargetView) m_pRenderTargetView->Release();
	//--------------------------------------------------------------------------------------
	// 백버퍼의 크기를 조정한다.
	//--------------------------------------------------------------------------------------
	DXGI_SWAP_CHAIN_DESC CurrentSD;
	m_pSwapChain->GetDesc(&CurrentSD);
	m_pSwapChain->ResizeBuffers(CurrentSD.BufferCount, iWidth, iHeight, CurrentSD.BufferDesc.Format, CurrentSD.Flags);
	m_pSwapChain->GetDesc(&m_SwapChainDesc);

	H_RETURN(SetRenderTargetView());
	H_RETURN(SetViewPort());

	if (FAILED(hr = CreateDxResource()))
	{
		return hr;
	}
	return S_OK;
}
//--------------------------------------------------------------------------------------
// DXGIFactory 인터페이스로부터 IDXGISwapChain 인터페이스를 생성한다.
//--------------------------------------------------------------------------------------
HRESULT TDevice::CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight, BOOL IsFullScreen)
{
	HRESULT hr = S_OK;
	SetFullScreenFlag(FALSE);
	if (m_pGIFactory == NULL) return S_FALSE;

	ZeroMemory(&m_SwapChainDesc, sizeof(m_SwapChainDesc));
	m_SwapChainDesc.BufferCount = 1;
	m_SwapChainDesc.BufferDesc.Width = iWidth;
	m_SwapChainDesc.BufferDesc.Height = iHeight;
	m_SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	m_SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	m_SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_SwapChainDesc.OutputWindow = hWnd;
	m_SwapChainDesc.SampleDesc.Count = 1;
	m_SwapChainDesc.SampleDesc.Quality = 0;
	m_SwapChainDesc.Windowed = !m_IsFullScreenMode;
	// 추가
	m_SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	U_RETURN(m_pGIFactory->CreateSwapChain(m_pd3dDevice, &m_SwapChainDesc, &m_pSwapChain));
}
//--------------------------------------------------------------------------------------
// ID3D11Device 인터페이스를 생성한다.
//--------------------------------------------------------------------------------------
HRESULT TDevice::CreateDevice()
{
	HRESULT hr;
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_driverType = driverTypes[driverTypeIndex];
		if (SUCCEEDED(hr = D3D11CreateDevice(NULL, m_driverType, NULL, createDeviceFlags,
			featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &m_pd3dDevice, &m_FeatureLevel, &m_pImmediateContext)))
		{
			if (FAILED(hr) || m_FeatureLevel < D3D_FEATURE_LEVEL_11_0)
			{
				if (m_pImmediateContext) m_pImmediateContext->Release();
				if (m_pd3dDevice) m_pd3dDevice->Release();
				continue;
			}
			break;
		}
	}
	H_RETURN(hr);

	return CreateGIFactory();
}
//--------------------------------------------------------------------------------------
// DXGIFactory 인터페이스를 생성한다.
//--------------------------------------------------------------------------------------
HRESULT TDevice::CreateGIFactory()
{
	if (m_pd3dDevice == NULL) return E_FAIL;
	HRESULT hr;// = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&m_pGIFactory) );
	IDXGIDevice * pDXGIDevice;
	hr = m_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);

	IDXGIAdapter * pDXGIAdapter;
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);

	IDXGIFactory * pIDXGIFactory;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&m_pGIFactory);

	pDXGIDevice->Release();
	pDXGIAdapter->Release();
	return hr;
}
//--------------------------------------------------------------------------------------
// DXGIFactory 인터페이스로부터 IDXGISwapChain 인터페이스를 생성한다.
//--------------------------------------------------------------------------------------

HRESULT TDevice::SetRenderTargetView()
{
	HRESULT hr = S_OK;
	// Create a render target view
	ID3D11Texture2D* pBackBuffer;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	H_RETURN(hr);

	hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	pBackBuffer->Release();
	H_RETURN(hr);

	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
	return S_OK;
}

HRESULT TDevice::SetViewPort()
{
	HRESULT hr = S_OK;

	// Setup the viewport    
	m_ViewPort.Width = m_SwapChainDesc.BufferDesc.Width;
	m_ViewPort.Height = m_SwapChainDesc.BufferDesc.Height;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_pImmediateContext->RSSetViewports(1, &m_ViewPort);

	g_rtClient.right = m_SwapChainDesc.BufferDesc.Width;
	g_rtClient.bottom = m_SwapChainDesc.BufferDesc.Height;
	return S_OK;
}
bool TDevice::CleanupDevice()
{
	// 초기 풀스크린윈도우에서 응용프로그램이 닫히는 경우에는 윈도우 전환 후에 
	// 객체들을 소멸해야 한다. (메모리 누수를 막을 수 있다.)
	m_pSwapChain->SetFullscreenState(false, NULL);

	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	if (m_pRenderTargetView) m_pRenderTargetView->Release();
	if (m_pSwapChain) m_pSwapChain->Release();
	if (m_pImmediateContext) m_pImmediateContext->Release();
	if (m_pd3dDevice) m_pd3dDevice->Release();
	if (m_pGIFactory) m_pGIFactory->Release();
	m_pd3dDevice = NULL;
	m_pSwapChain = NULL;
	m_pRenderTargetView = NULL;
	m_pImmediateContext = NULL;
	m_pGIFactory = NULL;
	return true;
}
TDevice::TDevice(void)
{
	m_driverType = D3D_DRIVER_TYPE_NULL;
	m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;
	m_pd3dDevice = NULL;
	m_pSwapChain = NULL;
	m_pRenderTargetView = NULL;
	m_pImmediateContext = NULL;
	m_pGIFactory = NULL;
}

TDevice::~TDevice(void)
{
}
