#include "TWindow.h"

TWindow* g_pWindow = NULL;
//--------------------------------------------------------------------------------------
// 메인 윈도우 프로시져
//--------------------------------------------------------------------------------------
LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    assert(g_pWindow);
    return g_pWindow->WndProc(hWnd, message, wParam, lParam);
}

//--------------------------------------------------------------------------------------
// 윈도우 프로시져
//--------------------------------------------------------------------------------------
LRESULT TWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
void TWindow::CenterWindow(HWND hwnd)
{
    // 화면 스크린의 해상도(넓이와 높이)을 얻는다.
    int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
    int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

    // 윈도우 클라이언트 중앙과 화면 스크린 중앙을 맞춘다.
    int iDestX = (iScreenWidth - (m_rcWindowBounds.right - m_rcWindowBounds.left)) / 2;
    int iDestY = (iScreenHeight - (m_rcWindowBounds.bottom - m_rcWindowBounds.top)) / 2;

    // 윈도우를 화면중앙으로 이동시킨다.
    MoveWindow(hwnd, iDestX, iDestY,
        m_rcWindowBounds.right - m_rcWindowBounds.left,
        m_rcWindowBounds.bottom - m_rcWindowBounds.top,
        true);
}
bool TWindow::InitWindow(HINSTANCE hInstance, int nCmdShow, CONST TCHAR* strWindowTitle)
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
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"TBasis3D11_Sample";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    if (!RegisterClassEx(&wcex))
        return false;

    // Create window
    m_hInstance = hInstance;
    RECT rc = { 0, 0, 800, 600 };
    // 작업영역(  타이틀 바/경계선/메뉴/스크롤 바 등의 영역을 제외한 영역), 윈도우 스타일, 메뉴여부
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    m_hWnd = CreateWindow(L"TBasis3D11_Sample", strWindowTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
        NULL);
    if (!m_hWnd)
        return false;


    // 윈도우 스타일을 저장하고 스크린 영역과 클라이언트 영역을 얻는다.
    m_dwWindowStyle = GetWindowLong(m_hWnd, GWL_STYLE);
    GetWindowRect(m_hWnd, &m_rcWindowBounds);
    GetClientRect(m_hWnd, &m_rcWindowClient);

    CenterWindow(m_hWnd);
    UpdateWindow(m_hWnd);

    // 윈도우 클라이언트 넓이와 높이를 얻는다.
    m_iWindowWidth = m_rcWindowClient.right - m_rcWindowClient.left;
    m_iWindowHeight = m_rcWindowClient.bottom - m_rcWindowClient.top;

    ShowWindow(m_hWnd, nCmdShow);
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
TWindow::TWindow()
{
    m_hInstance = NULL;
    m_hWnd = NULL;
    g_pWindow = this;
}

TWindow::~TWindow()
{
}
