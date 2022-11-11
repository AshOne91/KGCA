#include "TWindow.h"

RECT  g_rtClient;
TWindow* g_pWindow = NULL;
//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK StaticWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	assert( g_pWindow );
    return g_pWindow->WndProc(hWnd, message, wParam, lParam);
}

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT TWindow::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch( message )
    {
		case WM_SIZE:
		{
			//if( SIZE_MAXHIDE == wParam ) // �ٸ� �����찡 �ִ�ȭ�Ǿ� ���� �����찡 ��������
			//if( SIZE_MAXIMIZED == wParam ) // �ִ�ȭ
			//if( SIZE_MAXSHOW == wParam ) // �ִ�ȭ �Ǿ� �� �����츦 ������ �� �ٽ� ���� ũ��� �����Ǿ� �� �����찡 ���϶�
			//if( SIZE_RESTORED == wParam )// ũ�Ⱑ ����Ǿ���� �� 
			if (SIZE_MINIMIZED != wParam) // �ּ�ȭ
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				if (m_bResizeDrag == false)
				{
					ResizeDevice(width, height);
				}
			}
		}break;
		case WM_EXITMENULOOP:// �޴� �۾����� ����� �ð� ����
		break;
		case WM_ENTERSIZEMOVE: // ������ ũ�� ���� ���콺�� �巡�� ����
		{
			m_bResizeDrag = !m_bResizeDrag;
		}break;
		case WM_EXITSIZEMOVE: // ������ ũ�� ���� ���콺�� �巡�� �����
		{
			if (SIZE_MINIMIZED != wParam) // �ּ�ȭ�� �ƴ� ��쿡
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				ResizeDevice(width, height);
				m_bResizeDrag = !m_bResizeDrag;
			}
		}break;
		//// ��üȭ�� ��忡�� �̵�/ũ������ �� �����ս� ����
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
	// �۾�����(  Ÿ��Ʋ ��/��輱/�޴�/��ũ�� �� ���� ������ ������ ����), ������ ��Ÿ��, �޴�����
	// AdjustWindowRect()�Լ��� ȣ���� �ֱ� ������ ������ �۾������� D3D ����̽��� ������� ������ ��ġ�ϰԵȴ�.
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