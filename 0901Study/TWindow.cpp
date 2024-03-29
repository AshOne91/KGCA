#include "TWindow.h"
HWND g_hWnd;
RECT g_rtClient;
TWindow* g_pWindow = nullptr;
LRESULT CALLBACK WndProc(
    HWND hWnd, 
    UINT message, 
    WPARAM wParam, 
    LPARAM lParam)
{    
    _ASSERT(g_pWindow);
    return g_pWindow->MsgProc(hWnd, message, wParam, lParam);
}
LRESULT TWindow::MsgProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    msglist.push_back(message);
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0); // 메세지큐에 직접 WM_QUIT
        break;
    }
    // 메세지 내가 처리 불가 니가 대신 해줘.
    return  DefWindowProc(hWnd, message, wParam, lParam);
}
BOOL TWindow::InitInstance(const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{
    m_csStyle = WS_OVERLAPPEDWINDOW;
    RECT rc = { 0,0,iWidth , iHeight };
    AdjustWindowRect(&rc, m_csStyle, FALSE);
    // 운영체제에 등록한 윈도우를 생성한다.
    msglist.clear();
    HWND hWnd = CreateWindowW(
        L"KGCA윈도우",
        szTitle,
        m_csStyle,
        0, 0,
        rc.right-rc.left, 
        rc.bottom-rc.top,
        nullptr, nullptr, 
        m_hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }
    m_hWnd = hWnd;
    g_hWnd = hWnd;
    ShowWindow(hWnd, SW_SHOW);
    GetWindowRect(hWnd, &m_rtWindow);
    GetClientRect(hWnd, &m_rtClient);
    g_rtClient = m_rtClient;

    m_iClientWidth = m_rtClient.right - m_rtClient.left;
    m_iClientHeight = m_rtClient.bottom - m_rtClient.top;
    CenterWindow(); 
    return TRUE;
}
void TWindow::CenterWindow()
{
    UINT iScreenWidht = GetSystemMetrics(SM_CXFULLSCREEN);
    UINT iScreenHieght = GetSystemMetrics(SM_CYFULLSCREEN);
    UINT cx, cy;
    cx = (iScreenWidht - (m_rtWindow.right - m_rtWindow.left)) * 0.5f;
    cy = (iScreenHieght - (m_rtWindow.bottom - m_rtWindow.top)) * 0.5f;
    MoveWindow(m_hWnd, cx, cy,
        m_rtWindow.right - m_rtWindow.left,
        m_rtWindow.bottom - m_rtWindow.top,
        true);
}
/// <summary>
///  운영체제에게 윈도우 등록
/// </summary>
/// <param name="hInstance"></param>
/// <returns></returns>
ATOM TWindow::MyRegisterClass()
{
    WNDCLASSEXW  wcex;    
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.hInstance = m_hInstance;
    wcex.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
    wcex.lpszClassName = L"KGCA윈도우";// 이름
    // 윈도우 메세지를 받을 함수를 지정한다.    
    wcex.lpfnWndProc = WndProc;  // 전화번호  
    wcex.hCursor = LoadCursor(nullptr, IDC_WAIT);
    return RegisterClassEx(&wcex);
}
bool		TWindow::SetWindow(HINSTANCE hInstance,
                     const WCHAR* szTitle, UINT iWidth, UINT iHeight)
{   
    // 윈도우 등록
    m_hInstance = hInstance;
    WORD ret = MyRegisterClass();
    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(szTitle, iWidth, iHeight))
    {
        return FALSE;
    }
    return true;
}
bool		TWindow::TCoreInit()
{
    return true;
}
bool		TWindow::TCoreFrame()
{
    return true;
}
bool		TWindow::TCoreRender()
{
    return true;
}
bool		TWindow::TCoreRelease()
{
    return true;
}
TWindow::TWindow()
{
    g_pWindow = this;
}
bool        TWindow::Run()
{
    if (TCoreInit() == false)
    {
        TCoreRelease();
        return false;
    }

    MSG msg = { 0, };
    m_bGameRun = true;

    m_fGameTimer = 0.0f;
    m_fElapseTimer = 10.0f;
    DWORD dwBeforeTime  = timeGetTime(); //(1000: 1초)
    UINT fps=0;
    UINT counter = 0;
    float fFps = 0.0f;
    while (m_bGameRun)
    {        
        if (WM_QUIT == msg.message)
        {
            break;
        }
        // 장점 : 메세지큐에 메세지가 없어도 반환됨.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg); // 메세지 번역
            DispatchMessage(&msg);  // 메세지 프로시져에 전달한다.
        }
        else
        {            
            if (!TCoreFrame() || !TCoreRender())
            {
                m_bGameRun = false;
            }
        }
        DWORD dwCurrentTime = timeGetTime();
        DWORD dwElapseTime = dwCurrentTime - dwBeforeTime;
        m_fElapseTimer = dwElapseTime / 1000.0f;
        m_fGameTimer += m_fElapseTimer;
        std::wstring timer = std::to_wstring(m_fGameTimer);
        dwBeforeTime = dwCurrentTime;

        counter++;
        fFps += m_fElapseTimer;
        if (fFps >= 1.0f)
        {
            fps = counter;
            counter = 0;
            fFps = fFps - 1.0f;
        }
        timer += L"   ";
        timer += std::to_wstring(fps);
        timer += L"\n";
        OutputDebugString(timer.c_str());
    }
    TCoreRelease();

    return true;
}
