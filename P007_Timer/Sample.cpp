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
		MessageBox( 0, _T("CreateDevice  ����"), _T("Fatal error"), MB_OK );
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
		MessageBox( 0, _T("Sample  �ʱ�ȭ ����"), _T("Fatal error"), MB_OK );
		return 0;
	}	
	ShowCursor ( TRUE );
	gSample.Run();	
	return 1;
}




//BOOL DrawFocusRect( HDC hDC, CONST RECT * lprc );//������ ��Ŀ�� Ȱ��ȭ �̹����� �׸���. 
//int FillRect( HDC hDC, CONST RECT *lprc, HBRUSH hbr );//Ư�� �귯���� ���θ� ü���. 
//
//int FrameRect( HDC hDC, CONST RECT *lprc, HBRUSH hbr );//1�ȼ��� �귯���� �ܰ����� ü���. 
//
//BOOL InvertRect( HDC hDC,  CONST RECT *lprc );//Rect ������ ���� ��Ų��.
//
//BOOL SetRect( LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom );//Rect ���� ����
//
//BOOL SetRectEmpty( LPRECT lprc );//����.
//
//BOOL CopyRect( LPRECT lprcDst, CONST RECT *lprcSrc );//�����Ѵ�.
//
//BOOL InflateRect( LPRECT lprc, int dx, int dy );//RECT Ȯ���ϱ�
//
//BOOL IntersectRect( LPRECT lprcDst,  CONST RECT *lprcSrc1,  CONST RECT *lprcSrc2 );//Rect1, Rect2�� ������ Rect�� ���Ѵ�.
//
//BOOL UnionRect(LPRECT lprcDst, CONST RECT *lprcSrc1, CONST RECT *lprcSrc2 );//Rect1, Rect2�� ������ Rect�� ���Ѵ�.
//
//BOOL SubtractRect( LPRECT lprcDst,  CONST RECT *lprcSrc1, CONST RECT *lprcSrc2 );//Rect1���� Rect2�� �� Rect�� ���Ѵ�.
//
//BOOL OffsetRect( LPRECT lprc,  int dx, int dy );//Rect�� x, y ��ŭ �̵��Ѵ�.
//
//BOOL IsRectEmpty( CONST RECT *lprc );//Rect�� ��� �ִ��� �˻��Ѵ�.
//
//BOOL EqualRect( CONST RECT *lprc1, CONST RECT *lprc2 );//Rect1�� Rect2�� ������ ���Ѵ�.
//
//BOOL PtInRect( CONST RECT *lprc,POINT pt );//Rect���� �ȿ� Point ��ǥ�� �ִ��� �˻��Ѵ�.
