#include "Sample.h"

Sample gSample;
//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT Sample::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{   	
    switch( message )
    {
		case WM_KEYDOWN:
        {
            switch( wParam )
            {
				case '0':
				{
					// 전체화면과 윈도우 모드 토글 변환(백 버퍼의 크기는 변화가 없다.)
					if( m_pSwapChain )
					{	
						BOOL IsScreenMode = FALSE;
						m_pSwapChain->GetFullscreenState( &IsScreenMode, NULL );
						m_pSwapChain->SetFullscreenState( !IsScreenMode, NULL );
						SetFullScreenFlag( IsScreenMode );
						assert( GetFullScreenFlag()  == IsScreenMode );
						if( IsScreenMode )
						{
							ShowWindow( hWnd, SW_SHOW );
						}
					}
				}break;
				// 윈도우 크기(해상도) 및 포맷 변경
                case '1':
					{							
						if( m_pSwapChain )
						{	
							DXGI_MODE_DESC desc;
							ZeroMemory(&desc, sizeof (desc));
							desc.Width = 1024;
							desc.Height = 768;
							desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
							desc.RefreshRate.Denominator = 0;
							desc.RefreshRate.Numerator = 0;
							desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
							desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
							// 윈도우 크기 및 해상도( 화면모드 ) 변경
							m_pSwapChain->ResizeTarget(&desc);												
						}		
					}
					break;                
				// 전체화면 모드로 전환 및 해상도 변경
				case '2':
					{		
						if( m_pSwapChain )
						{	
							DXGI_MODE_DESC desc;
							ZeroMemory(&desc, sizeof (desc));
							desc.Width = 800;
							desc.Height = 600;
							desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
							desc.RefreshRate.Denominator = 0;
							desc.RefreshRate.Numerator = 0;
							desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
							desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

							// 윈도우 크기(해상도) 변경
							m_pSwapChain->ResizeTarget(&desc);							
							m_pSwapChain->SetFullscreenState( TRUE, NULL );							
						}
					}
					break;			
				case VK_ESCAPE:
				{
					SendMessage( hWnd, WM_CLOSE, 0, 0 );
					break;
				}
			}	
			break;
		}		
    }

    return TWindow::WndProc( hWnd, message, wParam, lParam );
}
bool Sample::Init()
{		
	if( FAILED( InitDevice(m_hWnd, m_iWindowWidth, m_iWindowHeight, m_IsFullScreenMode) ) )
	{
		MessageBox( 0, _T("CreateDevice  실패"), _T("Fatal error"), MB_OK );
		return false;
	}	
	return true;
}
bool Sample::Render()
{	
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red,green,blue,alpha
	m_pImmediateContext->ClearRenderTargetView( m_pRenderTargetView, ClearColor );
	
	m_pSwapChain->Present( 0, 0 );
	return true;
}
bool Sample::Release()
{	
	if( !CleanupDevice() ) return false;	
	return true;
}
Sample::Sample(void)
{
	m_IsFullScreenMode = TRUE;
}

Sample::~Sample(void)
{
}

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	Sample gSample;
	if( !gSample.InitWindow( hInstance, nCmdShow,  L"FullScreeenDevice" , gSample.m_IsFullScreenMode ) )
	{
		MessageBox( 0, _T("Sample  초기화 실패"), _T("Fatal error"), MB_OK );
		return 0;
	}	
	ShowCursor ( TRUE );
	gSample.Run();	
	return 1;
}