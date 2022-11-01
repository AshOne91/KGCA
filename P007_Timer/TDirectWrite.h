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
	// �ʱ�ȭ
	bool				Set(HWND hWnd, IDXGISurface1*	m_pSurface);
    bool				Init();
	// ������
	bool				Begin();
	HRESULT				DrawText(RECT rc, TCHAR* pText, D2D1::ColorF Color= D2D1::ColorF( 1,0,0,1 ) );
	bool				End();
	// ��ü �Ҹ�
	bool				Release();	
	// ��ü ���� �� �Ҹ�
    HRESULT				CreateDeviceIndependentResources();
    void				DiscardDeviceIndependentResources();    
	HRESULT				CreateDeviceResources(IDXGISurface1*	m_pSurface);
    void				DiscardDeviceResources();
	// ȭ�� ������ ����
	void				OnResize(UINT width, UINT height, IDXGISurface1*pSurface   );
public:
    TDirectWrite();
    ~TDirectWrite();
    
};
