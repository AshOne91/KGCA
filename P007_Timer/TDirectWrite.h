#pragma once
#include "TDefine.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
//#include <wincodec.h>
#pragma comment( lib, "d2d1.lib" )
#pragma comment( lib, "dwrite.lib" )


class TDirectWrite
{
public:
	float					m_fDPIScaleX;
    float					m_fDPIScaleY;	
	FLOAT					m_fdpiX;
    FLOAT					m_fdpiY;
	HWND					m_hWnd;
	ID2D1RenderTarget*		m_pRT;
    ID2D1Factory*			m_pD2DFactory;
    ID2D1SolidColorBrush*	m_pBlackBrush;
    IDWriteFactory*			m_pDWriteFactory;
    IDWriteTextFormat*		m_pTextFormat;   
public:
	// 초기화
	bool				Set(HWND hWnd, IDXGISurface1*	m_pSurface);
    bool				Init();
	// 랜더링
	bool				Begin();
	HRESULT				DrawText(RECT rc, TCHAR* pText, D2D1::ColorF Color= D2D1::ColorF( 1,0,0,1 ) );
	bool				End();
	// 전체 소멸
	bool				Release();	
	// 객체 생성 및 소멸
    HRESULT				CreateDeviceIndependentResources();
    void				DiscardDeviceIndependentResources();    
	HRESULT				CreateDeviceResources(IDXGISurface1*	m_pSurface);
    void				DiscardDeviceResources();
	// 화면 사이즈 변경
	void				OnResize(UINT width, UINT height, IDXGISurface1*pSurface   );
public:
    TDirectWrite();
    ~TDirectWrite();
    
};
