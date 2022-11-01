#include "TDirectWrite.h"
#include <math.h>
#pragma comment (lib, "winmm.lib")  

template <class T> inline void SafeRelease(T **ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

bool TDirectWrite::Set(HWND hWnd, IDXGISurface1*	pSurface)
{
	HRESULT hr;	
	m_hWnd = hWnd;
	if( !Init() )
	{
		return false;
	}
	V( CreateDeviceResources(pSurface));
	return true;	
}

TDirectWrite::TDirectWrite() :   
    m_pD2DFactory(NULL),
    m_pBlackBrush(NULL),
    m_pDWriteFactory(NULL),
    m_pTextFormat(NULL)
{
	m_pD2DFactory = NULL;
	m_pRT = NULL;
}
bool TDirectWrite::Release()
{
   DiscardDeviceIndependentResources();
   DiscardDeviceResources();
	return true;
}

TDirectWrite::~TDirectWrite()
{
	Release();
}
bool TDirectWrite::Init()
{   	
	HRESULT hr;
	V(CreateDeviceIndependentResources());
    return true;
}
HRESULT TDirectWrite::CreateDeviceIndependentResources()
{
    HRESULT hr;
	 // Create Direct2D factory.
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,&m_pD2DFactory);

	//m_pD2DFactory->GetDesktopDpi(&m_fdpiX, &m_fdpiY);
	m_fDPIScaleX = 96.0f;
    m_fDPIScaleY = 96.0f;	

    // Create a shared DirectWrite factory.
    if (SUCCEEDED(hr))
    {
        hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(IDWriteFactory),reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
    } 
    // Create a text format using Gabriola with a font size of 72.
    // This sets the default font, weight, stretch, style, and locale.
    if (SUCCEEDED(hr))
    {
        hr = m_pDWriteFactory->CreateTextFormat(
            L"±Ã¼­",                 // Font family name.
            NULL,                        // Font collection (NULL sets it to use the system font collection).
            DWRITE_FONT_WEIGHT_REGULAR,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            20.0f,
            L"ko-kr",
            &m_pTextFormat
            );
    }    
    return hr;
}
void TDirectWrite::DiscardDeviceIndependentResources()
{
    SafeRelease(&m_pD2DFactory);
    SafeRelease(&m_pDWriteFactory);
    SafeRelease(&m_pTextFormat);
}
HRESULT TDirectWrite::DrawText( RECT rc, TCHAR* pText,  D2D1::ColorF Color )
{
	if(m_pRT&&m_pBlackBrush)
	{
		D2D1_RECT_F layoutRect = D2D1::RectF(
			static_cast<FLOAT>(rc.left) / m_fDPIScaleX,
			static_cast<FLOAT>(rc.top) /  m_fDPIScaleY,
			static_cast<FLOAT>(rc.right) / m_fDPIScaleX,
			static_cast<FLOAT>(rc.bottom) / m_fDPIScaleY   );  
		m_pBlackBrush->SetColor( Color   );
		m_pRT->DrawText( pText, wcslen(pText), m_pTextFormat, layoutRect, m_pBlackBrush  	);
	}
	return S_OK;
}
bool TDirectWrite::Begin()
{
	if( m_pRT )
	{
		m_pRT->BeginDraw();
	/*	D2D_MATRIX_3X2_F mat;
		mat._11 = cosf(fTime); mat._12 = -sinf(fTime); 
		mat._21 = sinf(fTime); mat._22 = cosf(fTime);
		mat._31 = 400; mat._32=300;*/
		m_pRT->SetTransform(D2D1::IdentityMatrix());
		// m_pRT->Clear(D2D1::ColorF(D2D1::ColorF::White));
	}
	return true;
}
bool TDirectWrite::End()
{
	if (m_pRT && FAILED(m_pRT->EndDraw()))
    {
       return false;
    }    
	return true;
}
HRESULT TDirectWrite::CreateDeviceResources( IDXGISurface1*	pSurface)
{
	HRESULT hr = S_OK;
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
											D2D1_RENDER_TARGET_TYPE_DEFAULT,
											D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
											static_cast<float>(m_fdpiX),
											static_cast<float>(m_fdpiY) );
	V_RETURN( m_pD2DFactory->CreateDxgiSurfaceRenderTarget( pSurface, (const D2D1_RENDER_TARGET_PROPERTIES *)&props, &m_pRT ) );
	V_RETURN( m_pRT->CreateSolidColorBrush(  D2D1::ColorF( D2D1::ColorF::Yellow ) ,   &m_pBlackBrush ) );
	return S_OK;
}
void TDirectWrite::DiscardDeviceResources()
{
    SafeRelease(&m_pRT);  
	SafeRelease(&m_pBlackBrush); 
}

void TDirectWrite::OnResize(UINT width, UINT height, IDXGISurface1*	pSurface)
{	
	CreateDeviceResources( pSurface );
}
