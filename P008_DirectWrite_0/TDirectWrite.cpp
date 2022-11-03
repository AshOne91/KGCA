#include "TDirectWrite.h"
#include <math.h>

template <class T> inline void SafeRelease(T **ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}
//////////////////////////////////////////////
// DX 매소드 호출에 대한 반환값 처리 매크로
//////////////////////////////////////////////
#ifndef V
	#define V(x)       { hr = (x); }
#endif
#ifndef V_RETURN
	#define V_RETURN(x){ hr = (x); if( FAILED(hr) ) { return hr; } }
#endif


bool TDirectWrite::Set(HWND hWnd, int iWidth, int iHeight, IDXGISurface1*	pSurface)
{
	HRESULT hr;	
	if( !Init() )
	{
		return false;
	}	
	m_hWnd = hWnd;
	
	V(CreateDeviceIndependentResources());
	V(CreateDeviceResources( pSurface ));
	SetText(D2D1::Point2F(iWidth, iHeight), L"TBasisSample!",D2D1::ColorF( 1,1,1,1 ));
	return true;	
}


bool TDirectWrite::Release()
{
	m_wszText.clear();
	m_wszFontFamily.clear();
	DiscardDeviceIndependentResources();
	DiscardDeviceResources();
	return true;
}


bool TDirectWrite::Init()
{   	
    const wchar_t defaultText [] = L"Gabriola";   
	m_wszFontFamily = defaultText;
    return true;
}
HRESULT TDirectWrite::CreateDeviceIndependentResources()
{
    HRESULT hr;
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,&m_pD2DFactory);

	//m_pD2DFactory->GetDesktopDpi(&m_fdpiX, &m_fdpiY);
    m_fdpiX = (FLOAT)GetDpiForWindow(GetDesktopWindow());
    m_fdpiY = m_fdpiX;
	m_fDPIScaleX = m_fdpiX / 96.0f;
    m_fDPIScaleY = m_fdpiY / 96.0f;	

    if (SUCCEEDED(hr))
    {
        hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(IDWriteFactory),reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
    } 
    if (SUCCEEDED(hr))
    {
        hr = m_pDWriteFactory->CreateTextFormat(
				m_wszFontFamily.c_str(),              
                NULL,                        
                m_fontWeight,
                m_fontStyle,
                DWRITE_FONT_STRETCH_NORMAL,
                20,
				L"en-us",//L"ko-kr",
				&m_pTextFormat
            );
    }   	
    return hr;
}
/******************************************************************
*                                                                 *
*  TextDialog::SetFont                                            *
*                                                                 *
*  This method sets the font family for the entire range of text  *
*  in the text layout object then redraws the text by using the   *
*  DrawD2DContent method of this class.                              *
*                                                                 *
******************************************************************/

HRESULT TDirectWrite::SetFont(const wchar_t *fontFamily)
{
    HRESULT hr;

    DWRITE_TEXT_RANGE textRange = {0, m_cTextLength};

    hr = m_pTextLayout->SetFontFamilyName(fontFamily, textRange);

    if (SUCCEEDED(hr))
    {
		m_wszFontFamily.clear();
		m_wszFontFamily = fontFamily;
    }
    return hr;
}

/******************************************************************
*                                                                 *
*  TextDialog::SetFontSize                                        *
*                                                                 *
*  This method sets the font size for the entire range of text    *
*  in the text layout object then redraws the text by using the   *
*  DrawD2DContent method of this class.                              *
*                                                                 *
******************************************************************/

HRESULT TDirectWrite::SetFontSize(float size)
{
    HRESULT hr;
    DWRITE_TEXT_RANGE textRange = {0, m_cTextLength};
    
    hr = m_pTextLayout->SetFontSize(size, textRange);

    if (SUCCEEDED(hr))
    {
        // Store the font size for later.
        m_fontSize = size;
    }
    return hr;
}
HRESULT TDirectWrite::SetText(D2D1_POINT_2F size, const wchar_t *text,D2D1::ColorF Color)
{
    HRESULT hr = S_OK;
    // Store the text for later.
    m_cTextLength = (UINT32) wcslen(text);
	m_wszText.clear();
   	m_wszText = text;   
    // Release any existing layout object.
    SafeRelease(&m_pTextLayout);    
    // Create a text layout using the text format.
    if (SUCCEEDED(hr))
    {
        hr = m_pDWriteFactory->CreateTextLayout(
			m_wszText.c_str(),           // The string to be laid out and formatted.
            m_cTextLength,       // The length of the string.
            m_pTextFormat,       // The text format to apply to the string (contains font information, etc).
            size.x,         // The width of the layout box.
            size.y,        // The height of the layout box.
            &m_pTextLayout       // The IDWriteTextLayout interface pointer.
            );
    }

	// Declare a typography pointer.
    IDWriteTypography* pTypography = NULL;
    // Create a typography interface object.
    if (SUCCEEDED(hr))
    {
        hr = m_pDWriteFactory->CreateTypography(&pTypography);
    }

    // Set the stylistic set.
    DWRITE_FONT_FEATURE fontFeature = {DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_7,1};
    if (SUCCEEDED(hr))
    {
        hr = pTypography->AddFontFeature(fontFeature);
    }

    // Set the typography for the entire string.
    DWRITE_TEXT_RANGE textRange = {0, m_cTextLength};

    if (SUCCEEDED(hr))
    {
        hr = m_pTextLayout->SetTypography(pTypography, textRange);
    }

    // Set the underline for the entire string.
    if (SUCCEEDED(hr))
    {
        hr = m_pTextLayout->SetUnderline(m_fontUnderline, textRange);
    }	
    SafeRelease(&pTypography);
    return hr;
}
/******************************************************************
*                                                                 *
*  TextDialog::SetBold                                            *
*                                                                 *
*  This method toggles the weight to and from bold for the        *
*  entire range of text in the text layout object then redraws    *
*  the text by using the DrawD2DContent method of this class.      *
*                                                                 *
******************************************************************/

HRESULT TDirectWrite::SetBold(bool bold)
{
    HRESULT hr;
    DWRITE_TEXT_RANGE textRange = {0, m_cTextLength};

    if (bold)
    {
        m_fontWeight = DWRITE_FONT_WEIGHT_BOLD;
    }
    else
    {
        m_fontWeight = DWRITE_FONT_WEIGHT_NORMAL;
    }
    
    // Set the font weight.
    hr = m_pTextLayout->SetFontWeight(m_fontWeight, textRange);
    return hr;
}

/******************************************************************
*                                                                 *
*  TextDialog::SetItalic                                          *
*                                                                 *
*  This method toggles the style to and from italic for the       *
*  entire range of text in the text layout object then redraws    *
*  the text by using the DrawD2DContent method of this class.      *
*                                                                 *
******************************************************************/

HRESULT TDirectWrite::SetItalic(bool italic)
{
    HRESULT hr;
    DWRITE_TEXT_RANGE textRange = {0, m_cTextLength};

    if (italic)
    {
        m_fontStyle = DWRITE_FONT_STYLE_ITALIC;
    }
    else
    {
        m_fontStyle = DWRITE_FONT_STYLE_NORMAL;
    }
    
    // Set the font style.
    hr = m_pTextLayout->SetFontStyle(m_fontStyle, textRange);
    return hr;
}

/******************************************************************
*                                                                 *
*  TextDialog::SetUnderline                                       *
*                                                                 *
*  This method sets toggles the underline for the entire range of *
*  text in the text layout object then redraws the text by using  *
*  the DrawD2DContent method of this class.                          *
*                                                                 *
******************************************************************/

HRESULT TDirectWrite::SetUnderline(bool underline)
{
    HRESULT hr;
    DWRITE_TEXT_RANGE textRange = {0, m_cTextLength};

    m_fontUnderline = underline;

    // Set the underline.
    hr = m_pTextLayout->SetUnderline(m_fontUnderline, textRange);
    return hr;
}
void TDirectWrite::DiscardDeviceIndependentResources()
{
    SafeRelease(&m_pD2DFactory);
    SafeRelease(&m_pDWriteFactory);
    SafeRelease(&m_pTextFormat);
	SafeRelease(&m_pTextLayout);
}
HRESULT TDirectWrite::DrawText( RECT rc, CONST TCHAR* pText,  D2D1::ColorF Color )
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
HRESULT TDirectWrite::DrawText(D2D1_POINT_2F pos, D2D1::ColorF Color)
{
    D2D1_POINT_2F origin = D2D1::Point2F(
		static_cast<FLOAT>(pos.x / m_fDPIScaleX),
        static_cast<FLOAT>(pos.y  / m_fDPIScaleY)     );
	m_pBlackBrush->SetColor( Color );
	
	DWRITE_TEXT_METRICS textMetrics = { 0 };
	m_pTextLayout->GetMetrics(&textMetrics);

	D2D1_POINT_2F center;	
	center.x = pos.x + textMetrics.layoutWidth / 2;// == textMetrics.left + textMetrics.width / 2;
	center.y = pos.y + textMetrics.layoutHeight / 2;// == textMetrics.top + textMetrics.height / 2;
	
	float fScale = 1+cosf(g_fGameTimer)*0.5f + 0.5f;
	D2D1::Matrix3x2F scale = D2D1::Matrix3x2F::Scale(fScale, fScale, center);
	D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(g_fGameTimer*100.0f, center);
	D2D1::Matrix3x2F trans = D2D1::Matrix3x2F::Translation(0, 0);
	D2D1_MATRIX_3X2_F matWorld;
	matWorld = scale * rot * trans;
	m_pRT->SetTransform(matWorld);

    m_pRT->DrawTextLayout(origin,m_pTextLayout,m_pBlackBrush   );
    return S_OK;
}
bool TDirectWrite::Begin()
{
	//D2D1::Matrix3x2F matWorld;
	//D2D1_POINT_2F center;
	//center.x = 400;
	//center.y = 300;
	//float fScale = (cosf(g_fGameTimer)*0.5f + 0.5f) * 10;
	//D2D1::Matrix3x2F scale = matWorld.Scale(fScale, fScale, center);
	//D2D1::Matrix3x2F rot = matWorld.Rotation(g_fGameTimer*100,center);
	//rot = scale * rot;
	//m_pRT->SetTransform(rot);
	//m_pRT->SetTransform(D2D1::Matrix3x2F::Translation(10.0f, 60.0f));
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
	D2D1_RENDER_TARGET_PROPERTIES props;// = D2D1::RenderTargetProperties(
										//	D2D1_RENDER_TARGET_TYPE_DEFAULT,
										//	D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
										//	static_cast<float>(m_fdpiX),
										//	static_cast<float>(m_fdpiY) );
	
	props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	props.pixelFormat= D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
	props.dpiX= static_cast<float>(m_fdpiX);
	props.dpiY= static_cast<float>(m_fdpiY);
	props.usage= D2D1_RENDER_TARGET_USAGE_NONE;
	props.minLevel= D2D1_FEATURE_LEVEL_DEFAULT;

	V_RETURN( m_pD2DFactory->CreateDxgiSurfaceRenderTarget(pSurface,&props,	&m_pRT ) );
	V_RETURN( m_pRT->CreateSolidColorBrush(D2D1::ColorF( D2D1::ColorF::Yellow ),&m_pBlackBrush ) );
	return S_OK;
}
void TDirectWrite::DiscardDeviceResources()
{
    SafeRelease(&m_pRT);  
	SafeRelease(&m_pBlackBrush); 
}
bool TDirectWrite::Render()
{
	m_pRT->BeginDraw();
	for (int iText = 0; iText < m_TextList.size(); iText++)
	{
		m_pRT->SetTransform(m_TextList[iText].matWorld);
		D2D1_RECT_F rf =
			m_TextList[iText].rf;
		rf.top += iText * 30.0f;
		m_pBlackBrush->SetColor(m_TextList[iText].color);

		m_pRT->DrawText(m_TextList[iText].pText.c_str(),
			m_TextList[iText].pText.size(),
			m_pTextFormat, rf, m_pBlackBrush);
	}
	m_pRT->EndDraw();
	return true;
}
void TDirectWrite::OnResize(UINT width, UINT height, IDXGISurface1*	pSurface)
{	
	DiscardDeviceResources();
	CreateDeviceResources( pSurface );
	SetText(D2D1::Point2F(width, height), L"TBasisSample!",D2D1::ColorF( 1,1,1,1 ));
}
TDirectWrite::TDirectWrite()  
{	
    m_pBlackBrush=NULL;
    m_pDWriteFactory=NULL;
	m_pTextFormat = NULL;
	m_pD2DFactory = NULL;
	m_pTextLayout = NULL;
	m_pRT = NULL;
	m_hWnd =NULL;
    m_cTextLength=0;
    m_fontWeight = DWRITE_FONT_WEIGHT_NORMAL;
    m_fontStyle=DWRITE_FONT_STYLE_NORMAL;
    m_fontUnderline=FALSE;
    m_fontSize=72.0f;
}
TDirectWrite::~TDirectWrite()
{
}