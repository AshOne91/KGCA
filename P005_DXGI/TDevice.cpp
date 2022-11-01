#include "TDevice.h"

static HMODULE                              s_hModDXGI					= NULL;
static HMODULE                              s_hModD3D11					= NULL;

typedef HRESULT ( WINAPI* LPCREATEDXGIFACTORY )( REFIID, void** );
typedef HRESULT ( WINAPI* LPD3D11CREATEDEVICE )(  __in_opt IDXGIAdapter* pAdapter,
													D3D_DRIVER_TYPE DriverType,
													HMODULE Software,
													UINT Flags,
													__in_ecount_opt( FeatureLevels ) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
													UINT FeatureLevels,
													UINT SDKVersion,
													__out_opt ID3D11Device** ppDevice,
													__out_opt D3D_FEATURE_LEVEL* pFeatureLevel,
													__out_opt ID3D11DeviceContext** ppImmediateContext);

static LPCREATEDXGIFACTORY                  s_DynamicCreateDXGIFactory	= NULL;
static LPD3D11CREATEDEVICE                  s_DynamicD3D11CreateDevice	= NULL;

static bool EnsureD3D10APIs( void )
{
    if( s_hModD3D11 != NULL || s_hModDXGI != NULL  )
        return true;

    // This may fail if Direct3D 10 isn't installed
    s_hModD3D11 = LoadLibrary( L"d3d11.dll" );
    if( s_hModD3D11 != NULL )
    {
        s_DynamicD3D11CreateDevice = ( LPD3D11CREATEDEVICE )GetProcAddress( s_hModD3D11, "D3D11CreateDevice" );      
    }

    s_hModDXGI = LoadLibrary( L"dxgi.dll" );
    if( s_hModDXGI )
    {
        s_DynamicCreateDXGIFactory = ( LPCREATEDXGIFACTORY )GetProcAddress( s_hModDXGI, "CreateDXGIFactory" );
    }
    return ( s_hModDXGI != NULL ) && ( s_hModD3D11 != NULL );
}

//--------------------------------------------------------------------------------------
// DXGIFactory 인터페이스를 생성한다.
//--------------------------------------------------------------------------------------
HRESULT TDevice::CreateGIFactory()
{	
	HRESULT hr;
	H_RETURN(s_DynamicCreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&m_pGIFactory)));	
	H_RETURN(m_Enumeration.Enumerate(m_pGIFactory));
	return hr;
}
//--------------------------------------------------------------------------------------
// DXGIFactory 인터페이스로부터 IDXGISwapChain 인터페이스를 생성한다.
//--------------------------------------------------------------------------------------
HRESULT TDevice::CreateSwapChain( HWND hWnd, UINT iWidth, UINT iHeight)
{	
	HRESULT hr = S_OK;
	if( m_pGIFactory == NULL ) return E_FAIL;	
	DXGI_MODE_DESC BufferDesc;
	ZeroMemory( &BufferDesc, sizeof( BufferDesc ) );
	BufferDesc.Width		= iWidth;
	BufferDesc.Height		= iHeight;
	BufferDesc.Format		= DXGI_FORMAT_R8G8B8A8_UNORM;
	BufferDesc.RefreshRate.Numerator = 60;
	BufferDesc.RefreshRate.Denominator = 1;

	// 적절한 화면 모드를 검색한다.
	DXGI_MODE_DESC FindBufferDesc;
	FindBufferDesc = FindClosestMatchingMode( BufferDesc, m_pd3dDevice );
	if( m_pGIFactory == NULL ) return S_FALSE;

	DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof( sd ) );
    sd.BufferCount		= 1;
	sd.BufferDesc		= FindBufferDesc;  	
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow		= hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = true;
	sd.Flags	= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	H(m_pGIFactory->CreateSwapChain(m_pd3dDevice, &sd, &m_pSwapChain));
	return hr;
}
HRESULT TDevice::SetRenderTargetView()
{
	HRESULT hr = S_OK;
    ID3D11Texture2D* pBackBuffer;
	H_RETURN(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer));
	H_RETURN(m_pd3dDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_pRenderTargetView ));
    m_pImmediateContext->OMSetRenderTargets( 1, &m_pRenderTargetView, NULL );
	return S_OK;
}

HRESULT TDevice::SetViewPort()
{
	HRESULT hr = S_OK;
	DXGI_SWAP_CHAIN_DESC Desc;
	m_pSwapChain->GetDesc( &Desc );
	// Setup the viewport    
    m_ViewPort.Width	= Desc.BufferDesc.Width;
    m_ViewPort.Height	= Desc.BufferDesc.Height;
    m_ViewPort.MinDepth = 0.0f;
    m_ViewPort.MaxDepth = 1.0f;
    m_ViewPort.TopLeftX = 0;
    m_ViewPort.TopLeftY = 0;	
	m_pImmediateContext->RSSetViewports( 1, &m_ViewPort );
	return S_OK;
}

bool TDevice::CleanupDevice()
{
	m_Enumeration.ClearAdapterInfoList();

	FreeLibrary( s_hModD3D11 );
	FreeLibrary( s_hModDXGI );

    if( m_pImmediateContext ) m_pImmediateContext->ClearState();	
    if( m_pRenderTargetView ) m_pRenderTargetView->Release();
    if( m_pSwapChain ) m_pSwapChain->Release();
	if( m_pImmediateContext ) m_pImmediateContext->Release();
    if( m_pd3dDevice ) m_pd3dDevice->Release();
	if( m_pGIFactory ) m_pGIFactory->Release();
	m_pd3dDevice		= NULL;
	m_pSwapChain		= NULL;
	m_pRenderTargetView = NULL;
	m_pImmediateContext = NULL;
	m_pGIFactory		= NULL;
	return true;
}
TDevice::TDevice(void)
{
	m_driverType		= D3D_DRIVER_TYPE_NULL;
	m_FeatureLevel		= D3D_FEATURE_LEVEL_11_0;
	m_pd3dDevice		= NULL;
	m_pSwapChain		= NULL;
	m_pRenderTargetView = NULL;
	m_pImmediateContext = NULL;
}

TDevice::~TDevice(void)
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------
// ID3D11Device 인터페이스를 생성한다.
//--------------------------------------------------------------------------------------
HRESULT TDevice::CreateDevice()
{	
	HRESULT hr;
	UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = sizeof( driverTypes ) / sizeof( driverTypes[0] );

	D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );
	
	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
    {
		 HMODULE wrp = NULL;
         m_driverType = driverTypes[driverTypeIndex];
        if( hr = s_DynamicD3D11CreateDevice( NULL, m_driverType, NULL, createDeviceFlags,featureLevels, numFeatureLevels,
                                            D3D11_SDK_VERSION, &m_pd3dDevice, &m_FeatureLevel, &m_pImmediateContext ))
		{
			if( FAILED( hr ) || m_FeatureLevel < D3D_FEATURE_LEVEL_11_0)
			{
				if( m_pImmediateContext ) m_pImmediateContext->Release();
				if( m_pd3dDevice ) m_pd3dDevice->Release();
				continue;
			}
			break;
		}

        if( SUCCEEDED( hr ) ) break;
    }
	U_RETURN(hr);
}

DXGI_MODE_DESC TDevice::FindClosestMatchingMode(DXGI_MODE_DESC& Desc, ID3D11Device* pd3dDevice )
{	
	HRESULT	hr;
	DXGI_MODE_DESC FindDesc;
	TEnumAdapter* pAdapterInfo;

    for( int i = 0; i < m_Enumeration.m_AdapterInfoList.size(); i++ )
    {
        pAdapterInfo = m_Enumeration.m_AdapterInfoList[i];	

		LARGE_INTEGER DriverVersion;//user mode driver version 
		if( pAdapterInfo->m_pAdapter->CheckInterfaceSupport(__uuidof(ID3D11Device), &DriverVersion) != DXGI_ERROR_UNSUPPORTED )		
		{
			continue;
		}
		TEnumOutput* pOutputInfo;
		for( int i = 0; i < pAdapterInfo->m_OutputInfoList.size(); i++ )
		{
			pOutputInfo = pAdapterInfo->m_OutputInfoList[i];
			if( SUCCEEDED( pOutputInfo->m_pOutput->FindClosestMatchingMode( &Desc, &FindDesc, pd3dDevice ) ))
			{
				return FindDesc;
			}
		}
	}
	return FindDesc;
}

bool TDevice::Start()
{
	if( !EnsureD3D10APIs() )
	{		
		WCHAR strBuffer[512];
		wcscpy_s( strBuffer, ARRAYSIZE(strBuffer), 
			L"This application requires a Direct3D 11 class\ndevice (hardware or reference rasterizer) running on Windows Vista Or Window7 (or later)." );
		MessageBox( 0, strBuffer,L"Could not initialize Direct3D 11", MB_OK );		
		return false;
	}
	return true;
}
