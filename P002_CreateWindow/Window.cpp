#include "Window.h"

Window* g_pWindow = nullptr;

LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	assert(g_pWindow);
	return g_pWindow->WndProc(hWnd, message, wParam, lParam);
}

bool Window::InitWindow(HINSTANCE hInstance, int nCmdShow, CONST TCHAR* strWindowTitle)
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = &StaticWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//wcex.hbrBackground = GreateSolidBrush(RGB(0, 255, 0));
	//wcex.hbrBackGround = CreateHatchBrush(HS_DIAGCROSS, RGB(0, 0, 255));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"TBasis3D11_Sample";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	if (!RegisterClassEx(&wcex))
		return false;

	// Create window
	_hInstance = hInstance;

	RECT rc = { 0, 0, 800, 600 };
	// 작업영역(  타이틀 바/경계선/메뉴/스크롤 바 등의 영역을 제외한 영역), 윈도우 스타일, 메뉴여부
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, //WS_EX_TOPMOST,// | WS_EX_TOOLWINDOW,
		L"TBasis3D11_Sample", strWindowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL);
	if (!_hWnd)
		return false;

	// 윈도우 스타일을 저장하고 스크린 영역과 클라이언트 영역을 얻는다.
	_dwWindowStyle = GetWindowLong(_hWnd, GWL_STYLE);
	GetWindowRect(_hWnd, &_rcWindowBounds);
	GetClientRect(_hWnd, &_rcWindowClient);

	CenterWindow(_hWnd);
	UpdateWindow(_hWnd);

	// 윈도우 클라이언트 넓이와 높이를 얻는다.
	_iWindowWidth = _rcWindowClient.right - _rcWindowClient.left;
	_iWindowHeight = _rcWindowClient.bottom - _rcWindowClient.top;

	ShowWindow(_hWnd, nCmdShow);
	return true;
}

void Window::CenterWindow(HWND hwnd)
{
	// 화면 스크린의 해상도(넓이와 높이)을 얻는다.
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

	// 윈도우 클라이언트 중앙과 화면 스크린 중앙을 맞춘다.
	int iDestX = (iScreenWidth - (_rcWindowBounds.right - _rcWindowBounds.left)) / 2;
	int iDestY = (iScreenHeight - (_rcWindowBounds.bottom - _rcWindowBounds.top)) / 2;

	// 윈도우를 화면중앙으로 이동시킨다.
	MoveWindow(hwnd, iDestX, iDestY,
		_rcWindowBounds.right - _rcWindowBounds.left,
		_rcWindowBounds.bottom - _rcWindowBounds.top,
		true);
}

bool Window::Init()
{
	return true;
}

bool Window::Frame()
{
	return true;
}

bool Window::Render()
{
	return true;
}

bool Window::Release()
{
	return true;
}

bool Window::Run()
{
	if (!Init()) return false;
	// Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (!Frame() || !Render())
			{
				break;
			}
		}
	}
	if (!Release()) return false;
	return true;
}

LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

Window::Window(void)
{
	_hInstance = NULL;
	_hWnd = NULL;
	g_pWindow = this;
}

Window::~Window(void)
{

}
