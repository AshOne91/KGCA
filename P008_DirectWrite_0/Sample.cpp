#include "Sample.h"

HRESULT Sample::ResizeDevice( UINT iWidth, UINT iHeight)
{	
	m_Font.DiscardDeviceResources();
	TDevice::ResizeDevice( iWidth, iHeight );
	
	if( m_pSwapChain != NULL )
	{
		HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (LPVOID*)&m_pBackBuffer);
		m_Font.OnResize( iWidth, iHeight,m_pBackBuffer);
		if( m_pBackBuffer )	m_pBackBuffer->Release();
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
	m_Timer.Init();
	HRESULT hr = GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (LPVOID*)&m_pBackBuffer);	
	m_Font.Set(m_hWnd, m_iWindowWidth, m_iWindowHeight, m_pBackBuffer );		
	if( m_pBackBuffer )	m_pBackBuffer->Release();
	return true;
}
bool Sample::Frame()
{
	return m_Timer.Frame();
}
bool Sample::Release()
{	
	if(!m_Timer.Release()) return false;
	if( !m_Font.Release() ) return false;		
	if( !CleanupDevice() ) return false;		
	return true;
}

bool Sample::Render()
{
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red,green,blue,alpha
	m_pImmediateContext->ClearRenderTargetView( m_pRenderTargetView, ClearColor );	
	
	if( m_Font.m_pTextFormat)
	{
		D2D1_SIZE_F rtSize = m_Font.m_pRT->GetSize ();
        //Draw a grid background.
        int width = static_cast <int> (rtSize.width);
        int height = static_cast <int> (rtSize.height);

		// 클라이언트 좌표계를 사용하여 RECT를 구성한다.
		m_Font.Begin();
			m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			// 단락(페러그래프)설정
			m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			RECT rc1 = {0,0, width, height/2};
			m_Font.DrawText(	rc1, 
								L"X축 좌측 정렬, Y축 상단 정렬",
								D2D1::ColorF(1,1,1,0.5));

			m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
			m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
			RECT rc2 = {0,0, width, height /2};
			m_Font.DrawText(rc2, L"X축 우측 정렬, Y축 하단 정렬",  D2D1::ColorF(1,1,1,0.5));

			m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			RECT rc3 = {0,0, width, height /2};
			m_Font.DrawText(rc3, L"X축 중앙 정렬, Y축 중앙 정렬",  D2D1::ColorF(1,1,1,0.5));

			m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
			RECT rc4 = { 0,height/2, width, height };
			m_Font.DrawText(rc4, L"X축 좌측 정렬, Y축 하단 정렬");

			m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
			m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			RECT rc5 = { 0,height / 2, width, height };
			m_Font.DrawText(rc5, L"X축 우측 정렬, Y축 상단 정렬");

			m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			RECT rc6 = { 0,height / 2, width, height };
			m_Font.DrawText(rc6, L"X축 중앙 정렬, Y축 상단 정렬");
		
		
			RECT rc;
			GetClientRect( m_hWnd,&rc);		
			m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

			rc.bottom   = rc.bottom / 2;		
			// bottom 와 right은 레이아웃의 가로/세로 크기이며 재설정 하면 Layout를 다시 생성하여야 한다.
			// top, left는 위치 이기 때문에 다시 생성하지 않아도 된다.
			// 레이아웃 최대 X = left + right
			// 레이아웃 최대 Y = top + bottom
			m_Font.SetText(D2D1::Point2F(rc.right, rc.bottom),L"KGCA Game Academy", D2D1::ColorF( 1,1,0,1 ));
			m_Font.SetFont(L"Gabriola");
			m_Font.SetBold(true);
			m_Font.SetFontSize( 40 );
			m_Font.SetItalic(true);
			m_Font.SetUnderline(true);
			// 레이아웃이 rc.left, rc.top로 이동하여 드로우 된다.
			m_Font.DrawText(D2D1::Point2F(rc.left, rc.top), D2D1::ColorF( 1,1,0,1 ));	

			rc.top		= m_iWindowHeight / 2;			
			m_Font.SetText(D2D1::Point2F(rc.right, rc.bottom),L"TBasis Sample", D2D1::ColorF( 1,1,0,1 ));
			m_Font.SetFont(L"Imprint MT Shadow");
			m_Font.SetBold(false);
			m_Font.SetFontSize( 70 );
			m_Font.SetItalic(false);
			m_Font.SetUnderline(false);
			m_Font.DrawText(D2D1::Point2F(rc.left, rc.top), D2D1::ColorF( 1,1,0,1 ));		
		m_Font.End();
	}
	
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
	if( !gSample.InitWindow( hInstance, nCmdShow,  L"DXFont / DXSprite" ) )
	{
		MessageBox( 0, _T("Sample  초기화 실패"), _T("Fatal error"), MB_OK );
		return 0;
	}	
	ShowCursor ( TRUE );
	gSample.Run();	
	return 1;
}