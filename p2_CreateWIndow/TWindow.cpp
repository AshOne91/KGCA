#include "TWindow.h"

ATOM TWindow::MyRegisterClass()
{
    WNDCLASSEXW wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.hInstance = m_hInstance;
    //wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.hbrBackground = CreateSolidBrush(RGB(128, 18, 39));
    wcex.lpfnWndProc = WndProc;
    wcex.lpszClassName = L"홍길동윈도우";
    wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
    //wcex.lpszMenuName

    return RegisterClassExW(&wcex);
}

LRESULT CALLBACK TWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

BOOL TWindow::InitInstance()
{
    HWND hWnd = CreateWindowW
        (L"홍길동윈도우"
        , L"여기는 우리집입니다."
        , WS_OVERLAPPEDWINDOW
        , CW_USEDEFAULT
        , 0
        , CW_USEDEFAULT
        , 0
        , nullptr
        , nullptr
        , m_hInstance
        , nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    //ShowWindow(hWnd, nCmdShow);
    ShowWindow(hWnd, SW_SHOW);
    //UpdateWindow(hWnd);

    return TRUE;
}

bool TWindow::Init()
{
    //윈도우 등록
    WORD ret = MyRegisterClass(m_hInstance);
    InitInstance();
    
    

	return false;
}

bool TWindow::Frame()
{
	return false;
}

bool TWindow::Render()
{
	return false;
}

bool TWindow::Release()
{
	return false;
}

bool TWindow::Run()
{
    MSG msg = { 0, };

    // 기본 메시지 루프입니다:
    while (WM_QUIT != msg.message)
    {
		//if (!TranslateAccelerator(msg.hwnd, /*hAccelTable*/0, &msg))
		//{
		//	TranslateMessage(&msg);
		//	DispatchMessage(&msg);
		//}

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Frame();
            Render();
        }
    }

    return true;
}
