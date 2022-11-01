#include "Sample.h"
HRESULT Sample::ResizeDevice(UINT iWidth, UINT iHeight)
{
	m_Font.DiscardDeviceResources();
	TDevice::ResizeDevice(iWidth, iHeight);

	if (m_pSwapChain != NULL)
	{
		HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (LPVOID*)&m_pBackBuffer);
		m_Font.OnResize(iWidth, iHeight, m_pBackBuffer);
		if (m_pBackBuffer)	m_pBackBuffer->Release();
	}
	return S_OK;
}
bool Sample::Init()
{	
	if( FAILED( InitDevice(m_hWnd,this->m_iWindowWidth, this->m_iWindowHeight) ) )
	{
		MessageBox( 0, _T("CreateDevice  실패"), _T("Fatal error"), MB_OK );
		return false;
	}

	if( !m_Timer.Init() )	return false;
	m_Timer.Start();

	IDXGISurface1*		pBackBuffer=NULL;
	HRESULT hr = GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (LPVOID*)&pBackBuffer);	
	m_Font.Set(m_hWnd, pBackBuffer );		
	if( pBackBuffer )	pBackBuffer->Release();

	return true;
}
bool Sample::Release()
{	
	m_Timer.Stop();
	if( !CleanupDevice() ) return false;	
	if( !m_Timer.Release() ) return false;		
	if( !m_Font.Release() ) return false;		
	return true;
}
bool  Sample::Frame()
{
	if( !m_Timer.Frame() ) return false;
	return true;
}

bool Sample::Render()
{
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red,green,blue,alpha
	m_pImmediateContext->ClearRenderTargetView( m_pRenderTargetView, ClearColor );
	
	

	TCHAR pBuffer[256];
	memset( pBuffer, 0, sizeof( TCHAR ) * 256 );
	_stprintf_s( pBuffer, _T("FPS:%d SecPerFrame:%10.5f Elapsed : %10.2f"),	m_Timer.GetFPS(), 
																			m_Timer.GetSPF(),
																			m_Timer.GetElapsedTime());	
	
	m_Font.Begin();
			m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			RECT rc1 = {0,0, m_iWindowWidth, m_iWindowHeight};
			m_Font.DrawText(rc1, pBuffer,  D2D1::ColorF(1,1,1,0.5));
	m_Font.End();

	m_pSwapChain->Present( 0, 0 );
	return true;
}	
Sample::Sample(void)
{
}

Sample::~Sample(void)
{
}

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	Sample gSample;
	if( !gSample.InitWindow( hInstance, nCmdShow,  L"Timer" ) )
	{
		MessageBox( 0, _T("Sample  초기화 실패"), _T("Fatal error"), MB_OK );
		return 0;
	}	
	ShowCursor ( TRUE );
	gSample.Run();	
	return 1;
}




//BOOL DrawFocusRect( HDC hDC, CONST RECT * lprc );//점선의 포커스 활성화 이미지를 그린다. 
//int FillRect( HDC hDC, CONST RECT *lprc, HBRUSH hbr );//특정 브러쉬로 내부를 체운다. 
//
//int FrameRect( HDC hDC, CONST RECT *lprc, HBRUSH hbr );//1픽셀의 브러쉬로 외곽선을 체운다. 
//
//BOOL InvertRect( HDC hDC,  CONST RECT *lprc );//Rect 영역을 반전 시킨다.
//
//BOOL SetRect( LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom );//Rect 영역 설정
//
//BOOL SetRectEmpty( LPRECT lprc );//비운다.
//
//BOOL CopyRect( LPRECT lprcDst, CONST RECT *lprcSrc );//복사한다.
//
//BOOL InflateRect( LPRECT lprc, int dx, int dy );//RECT 확장하기
//
//BOOL IntersectRect( LPRECT lprcDst,  CONST RECT *lprcSrc1,  CONST RECT *lprcSrc2 );//Rect1, Rect2의 교집합 Rect를 구한다.
//
//BOOL UnionRect(LPRECT lprcDst, CONST RECT *lprcSrc1, CONST RECT *lprcSrc2 );//Rect1, Rect2의 합집합 Rect를 구한다.
//
//BOOL SubtractRect( LPRECT lprcDst,  CONST RECT *lprcSrc1, CONST RECT *lprcSrc2 );//Rect1에서 Rect2를 뺀 Rect를 구한다.
//
//BOOL OffsetRect( LPRECT lprc,  int dx, int dy );//Rect를 x, y 만큼 이동한다.
//
//BOOL IsRectEmpty( CONST RECT *lprc );//Rect가 비어 있는지 검사한다.
//
//BOOL EqualRect( CONST RECT *lprc1, CONST RECT *lprc2 );//Rect1과 Rect2가 같은지 비교한다.
//
//BOOL PtInRect( CONST RECT *lprc,POINT pt );//Rect영역 안에 Point 좌표가 있는지 검사한다.
