#include "TWindow.h"
#include "TInput.h"

RECT  g_rtClient;
TWindow* g_pWindow = NULL;
//--------------------------------------------------------------------------------------
// 메인 윈도우 프로시져
//--------------------------------------------------------------------------------------
LRESULT CALLBACK StaticWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	assert( g_pWindow );
    return g_pWindow->WndProc(hWnd, message, wParam, lParam);
}

//--------------------------------------------------------------------------------------
// 윈도우 프로시져
//--------------------------------------------------------------------------------------
LRESULT TWindow::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch( message )
    {
		case WM_ACTIVATE:
		{
			if (WA_INACTIVE == wParam)
				m_bActive = FALSE;
			else
				m_bActive = TRUE;

			// DXInput가 독점모드일 경우에는 Set exclusive mode access to the mouse based on active state
			I_Input.SetAcquire(m_bActive);
			return 0;
		}

		case WM_KEYDOWN:
        {
			switch( wParam )
			{
				case '~':
				{
					if( GetSwapChain() )
					{		
						BOOL IsScreenMode = FALSE;
						GetSwapChain()->GetFullscreenState( &IsScreenMode, NULL );
						GetSwapChain()->SetFullscreenState( !IsScreenMode, NULL );
						SetFullScreenFlag( IsScreenMode );
						assert( GetFullScreenFlag()  == IsScreenMode );
						if( IsScreenMode )
						{
							ShowWindow( hWnd, SW_SHOW );
						}
					}
				}break;
			}
		}break;
		case WM_SIZE:
		{
			//if( SIZE_MAXHIDE == wParam ) // 다른 윈도우가 최대화되어 현재 윈도우가 가려지면
			//if( SIZE_MAXIMIZED == wParam ) // 최대화
			//if( SIZE_MAXSHOW == wParam ) // 최대화 되어 현 윈도우를 가려진 후 다시 원래 크기로 복구되어 이 윈도우가 보일때
			//if( SIZE_RESTORED == wParam )// 크기가 변경되어었을 때 
			if (SIZE_MINIMIZED != wParam) // 최소화
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				if (m_bResizeDrag == false)
				{
					ResizeDevice(width, height);
				}
			}
		}break;
		case WM_EXITMENULOOP:// 메뉴 작업에서 경과한 시간 무시
			break;
		case WM_ENTERSIZEMOVE: // 윈도우 크기 변경 마우스의 드래그 시작
		{
			m_bResizeDrag = !m_bResizeDrag;
		}break;
		case WM_EXITSIZEMOVE: // 윈도우 크기 변경 마우스의 드래그 종료시
		{
			if (SIZE_MINIMIZED != wParam) // 최소화가 아닐 경우에
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				ResizeDevice(width, height);
				m_bResizeDrag = !m_bResizeDrag;
			}
		}break;
		//// 전체화면 모드에서 이동/크기조정 및 전원손실 방지
		//case WM_SYSCOMMAND: 
		//	switch (wParam)
		//	{
		//		case SC_MOVE:
		//		case SC_SIZE:
		//		case SC_MAXIMIZE:
		//		case SC_MONITORPOWER:
		//		return TRUE;
		//	}
		//	break;
		case WM_CLOSE:
        {
            HMENU hMenu;
            hMenu = GetMenu( hWnd );
            if( hMenu != NULL )      DestroyMenu( hMenu );
            DestroyWindow( hWnd );
            UnregisterClass( L"TBasis3D11_Sample", NULL );            
            return 0;
        }
		case WM_DESTROY:
            PostQuitMessage( 0 );
            break;        
    }
    return DefWindowProc( hWnd, message, wParam, lParam );
}
void TWindow::CenterWindow(HWND hwnd)
{
	// get the width and height of the screen
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeight= GetSystemMetrics(SM_CYFULLSCREEN);

	// do the centering math
	int iDestX = (iScreenWidth-(m_rcWindowBounds.right-m_rcWindowBounds.left)) / 2;
	int iDestY = (iScreenHeight-(m_rcWindowBounds.bottom-m_rcWindowBounds.top)) / 2;

	// center the window
	MoveWindow( hwnd, iDestX, iDestY, 
				m_rcWindowBounds.right-m_rcWindowBounds.left,
				m_rcWindowBounds.bottom-m_rcWindowBounds.top,
				true);
}
bool TWindow::InitWindow(HINSTANCE hInstance, int nCmdShow, CONST TCHAR* strWindowTitle, BOOL IsFullScreen)
{
	  // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &StaticWndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"TBasis3D11_Sample";
    wcex.hIconSm = LoadIcon( wcex.hInstance,MAKEINTRESOURCE(IDI_APPLICATION) );
    if( !RegisterClassEx( &wcex ) )
        return false;

    // Create window
    m_hInstance = hInstance;
    RECT rc = { 0, 0, 800, 600 };
	// 작업영역(  타이틀 바/경계선/메뉴/스크롤 바 등의 영역을 제외한 영역), 윈도우 스타일, 메뉴여부
	// AdjustWindowRect()함수의 호출이 있기 때문에 윈도우 작업영역과 D3D 디바이스의 백버퍼의 영역이 일치하게된다.
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    m_hWnd = CreateWindow( L"TBasis3D11_Sample",strWindowTitle, WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
                           NULL );
    if( !m_hWnd )
        return false;

	// Save window properties
	m_dwWindowStyle = GetWindowLong( m_hWnd, GWL_STYLE );
	GetWindowRect( m_hWnd, &m_rcWindowBounds );
	GetClientRect( m_hWnd, &m_rcWindowClient );

	g_rtClient = m_rcWindowClient;

	CenterWindow(m_hWnd);
	UpdateWindow(m_hWnd);	

	m_iWindowWidth		= 	m_rcWindowClient.right - m_rcWindowClient.left;
	m_iWindowHeight		=	m_rcWindowClient.bottom-m_rcWindowClient.top;
	
	//RECT rtStart = m_rcWindowClient;
	//ClientToScreen( m_hWnd, (LPPOINT)&rtStart );
	//SetCursorPos( rtStart.left, rtStart.top );

	ShowWindow( m_hWnd, nCmdShow );
	return true;
}
bool TWindow::Init()
{
	return true;
}
bool TWindow::Frame()
{
	return true;
}
bool TWindow::Render()
{
	return true;
}
bool TWindow::Release()
{
	return true;
}
bool TWindow::Run()
{
	if( !Init() ) return false;
	// Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
			if( !Frame() ||  !Render() ) 
			{
				break;
			}
        }
    }
	if( !Release() ) return false;
	return true;
}
TWindow::TWindow(void)
{
	m_bResizeDrag		= false;
	m_hInstance			= NULL;
	m_hWnd				= NULL;
	g_pWindow			= this;
}

TWindow::~TWindow(void)
{
}
