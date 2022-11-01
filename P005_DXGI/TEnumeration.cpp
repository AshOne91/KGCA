#include "TEnumeration.h"

//--------------------------------------------------------------------------------------
TEnumOutput::~TEnumOutput()
{
    SAFE_RELEASE( m_pOutput );
    m_DisplayModeList.clear();
}
//--------------------------------------------------------------------------------------
TEnumDevice::~TEnumDevice()
{
}
void TEnumOutput::Set(UINT iIndex, IDXGIOutput* pOutput)
{
	 m_Output			= iIndex;     
     m_pOutput			= pOutput;
	 pOutput->GetDesc( &m_Desc );
}
//--------------------------------------------------------------------------------------
TEnumAdapter::~TEnumAdapter( void )
{
   TEnumDevice* pDeviceInfo;
    for( int i = 0; i < m_DeviceInfoList.size(); i++ )
    {
        pDeviceInfo = m_DeviceInfoList[i];
        SAFE_DEL(pDeviceInfo);
    }
    m_DeviceInfoList.clear();

	TEnumOutput* pOutputInfo;
    for( int i = 0; i < m_OutputInfoList.size(); i++ )
    {
        pOutputInfo = m_OutputInfoList[i];
        SAFE_DEL(pOutputInfo);
    }
    m_OutputInfoList.clear();

    SAFE_RELEASE( m_pAdapter );
}

void TEnumAdapter::Set(UINT iIndex, IDXGIAdapter* pAdapter)
{
	 m_AdapterOrdinal	= iIndex;     
     m_pAdapter			= pAdapter;
	 pAdapter->GetDesc( &m_AdapterDesc );
}
HRESULT TEnumeration::Enumerate(IDXGIFactory* pFactory)
{
    HRESULT hr;
    if( pFactory == NULL )      return E_FAIL;

    ClearAdapterInfoList();

    for( int index = 0; ; ++index )
    {
        IDXGIAdapter* pAdapter = NULL;
        
		hr = pFactory->EnumAdapters( index, &pAdapter );
        if( FAILED( hr ) ) break;

		TEnumAdapter* pAdapterInfo = 0;
		SAFE_NEW(  pAdapterInfo, TEnumAdapter);

        if( !pAdapterInfo )
        {
            return E_OUTOFMEMORY;
        }
       
		pAdapterInfo->Set( index, pAdapter );

        hr = EnumerateDevices( pAdapterInfo );
        if( FAILED( hr ) )
        {
            delete pAdapterInfo;
            continue;
        }

        hr = EnumerateOutputs( pAdapterInfo );
		if( FAILED( hr ) || pAdapterInfo->m_OutputInfoList.size() <= 0 )
        {
            delete pAdapterInfo;
            continue;
        }

		m_AdapterInfoList.push_back( pAdapterInfo );       
    }  
    return S_OK;
}
//--------------------------------------------------------------------------------------
HRESULT TEnumeration::EnumerateDevices( TEnumAdapter* pAdapterInfo )
{
    HRESULT hr;
	D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
	const D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );
    const UINT devTypeArrayCount = sizeof( driverTypes ) / sizeof( driverTypes[0] );

	for( UINT iDeviceType = 0; iDeviceType < devTypeArrayCount; iDeviceType++ )
    {
		TEnumDevice* pDeviceInfo = 0;
		SAFE_NEW(  pDeviceInfo, TEnumDevice);
        if( pDeviceInfo == NULL )      return E_OUTOFMEMORY;

        pDeviceInfo->m_AdapterOrdinal = pAdapterInfo->m_AdapterOrdinal;
        pDeviceInfo->DeviceType = driverTypes[iDeviceType];

        ID3D11Device*			pd3dDevice = NULL;
		ID3D11DeviceContext*    pImmediateContext =NULL;
        IDXGIAdapter*			pAdapter = NULL;

		D3D_DRIVER_TYPE ddt = driverTypes[iDeviceType];
        if( driverTypes[iDeviceType] == D3D_DRIVER_TYPE_HARDWARE )
		{
            pAdapter = pAdapterInfo->m_pAdapter;
			ddt = D3D_DRIVER_TYPE_UNKNOWN; 
		}

		
		D3D_FEATURE_LEVEL getFeatureLevel;
        hr = D3D11CreateDevice( pAdapter, ddt, ( HMODULE )0, NULL,
                                featureLevels, numFeatureLevels,
                                D3D11_SDK_VERSION, &pd3dDevice, &getFeatureLevel,&pImmediateContext );
        if( FAILED( hr ) )
        {
            delete pDeviceInfo;
            continue;
        }

		D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS ho;
        pd3dDevice->CheckFeatureSupport(D3D11_FEATURE_D3D10_X_HARDWARE_OPTIONS, &ho, sizeof(ho));

		SAFE_RELEASE( pd3dDevice);
		SAFE_RELEASE( pImmediateContext);

        pAdapterInfo->m_DeviceInfoList.push_back( pDeviceInfo );
    }

    return S_OK;
}

//--------------------------------------------------------------------------------------
HRESULT TEnumeration::EnumerateOutputs( TEnumAdapter* pAdapterInfo )
{
    HRESULT hr;
    IDXGIOutput* pOutput;

    for( int iOutput = 0; ; ++iOutput )
    {
        pOutput = NULL;
        hr = pAdapterInfo->m_pAdapter->EnumOutputs( iOutput, &pOutput );
        if( DXGI_ERROR_NOT_FOUND == hr )
        {
            return S_OK;
        }
        else if( FAILED( hr ) )
        {
            return hr;	//Something bad happened.
        }
        else //Success!
        {
            TEnumOutput* pOutputInfo = new TEnumOutput;
            if( !pOutputInfo )
            {
				SAFE_RELEASE( pOutput);
                return E_OUTOFMEMORY;
            }
			pOutputInfo->Set( iOutput, pOutput );

            EnumerateDisplayModes( pOutputInfo );
            if( pOutputInfo->m_DisplayModeList.size() <= 0 )
            {
                // If this output has no valid display mode, do not save it.
                delete pOutputInfo;
                continue;
            }

			pAdapterInfo->m_OutputInfoList.push_back( pOutputInfo );            
        }
    }
}
//--------------------------------------------------------------------------------------
HRESULT TEnumeration::EnumerateDisplayModes( TEnumOutput* pOutputInfo )
{
    HRESULT hr = S_OK;
    DXGI_FORMAT allowedAdapterFormatArray[] =
        {
            DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,     //This is DXUT's preferred mode
            DXGI_FORMAT_R8G8B8A8_UNORM,			
            DXGI_FORMAT_R16G16B16A16_FLOAT, 
			DXGI_FORMAT_R10G10B10A2_UNORM
        };
    int allowedAdapterFormatArrayCount = sizeof( allowedAdapterFormatArray ) / sizeof( allowedAdapterFormatArray[0] );

    for( int f = 0; f < allowedAdapterFormatArrayCount; ++f )
    {
		 UINT NumModes = 512;
		 hr = pOutputInfo->m_pOutput->GetDisplayModeList( allowedAdapterFormatArray[f],
                                                         DXGI_ENUM_MODES_SCALING,
                                                         &NumModes,
                                                         0 );

        DXGI_MODE_DESC* pDesc = new DXGI_MODE_DESC[ NumModes ];
        assert( pDesc );
        if( !pDesc )
            return E_OUTOFMEMORY;

        hr = pOutputInfo->m_pOutput->GetDisplayModeList( allowedAdapterFormatArray[f],
                                                         DXGI_ENUM_MODES_SCALING,
                                                         &NumModes,
                                                         pDesc );
        if( DXGI_ERROR_NOT_FOUND == hr )
        {
            SAFE_DELETE_ARRAY( pDesc );
            NumModes = 0;
            break;
        }           
        if( SUCCEEDED( hr ) )
        {
            for( UINT m = 0; m < NumModes; m++ )
            {
				if( pDesc[m].Width >= 800 && pDesc[m].Height >= 600 )
				{
					pOutputInfo->m_DisplayModeList.push_back( pDesc[m] );
				}
            }
        }
        SAFE_DELETE_ARRAY( pDesc );
    }
    return hr;
}



void TEnumeration::ClearAdapterInfoList()
{
    TEnumAdapter* pAdapterInfo;
    for( int i = 0; i < m_AdapterInfoList.size(); i++ )
    {
        pAdapterInfo = m_AdapterInfoList[i];
        SAFE_DEL( pAdapterInfo );
    }

    m_AdapterInfoList.clear();
}
TEnumeration::TEnumeration(void)
{
}

TEnumeration::~TEnumeration(void)
{
}
