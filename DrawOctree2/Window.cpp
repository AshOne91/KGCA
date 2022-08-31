#include "WIndow.h"
HWND g_hWnd;
RECT g_rtClient;
Window* g_pWIndow = nullptr;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	_ASSERT(g_pWIndow);
	return g_pWIndow->MsgProc(hWnd, message, wParam, lParam);
}

LRESULT Window::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	msglist.push_back(message);
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool Window::SetWindow(HINSTANCE hInst, const TCHAR* szTitle, UINT iWidth, UINT iHeight)
{
	_hInstance = hInst;
	WORD ret = MyRegisterClass();
	if (!InitInstance(szTitle, iWidth, iHeight))
	{
		return false;
	}
	return true;
}

ATOM Window::MyRegisterClass()
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance = _hInstance;
	wcex.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
	wcex.lpszClassName = L"KGCA윈도우";
	wcex.lpfnWndProc = WndProc;
	wcex.hCursor = LoadCursor(nullptr, IDC_WAIT);
	return RegisterClassEx(&wcex);
}

BOOL Window::InitInstance(const TCHAR* szTitle, UINT iWidth, UINT iHeight)
{
	_csStyle = WS_OVERLAPPEDWINDOW;
	RECT rc = { 0, 0, iWidth, iHeight };
	AdjustWindowRect(&rc, _csStyle, FALSE);

	msglist.clear();
	HWND hWnd = CreateWindow(L"KGCA윈도우", szTitle, _csStyle, 0, 0, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, _hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	_hWnd = hWnd;
	g_hWnd = hWnd;
	ShowWindow(hWnd, SW_SHOW);
	GetWindowRect(hWnd, &_rtWIndow); //화면 기준 좌표
	GetClientRect(hWnd, &_rtClient);
	_rtClient = _rtClient;

	_iClientWidth = _rtClient.right - _rtClient.left;
	_iClientHeight = _rtClient.bottom - _rtClient.top;
	CenterWIndow();
	return 0;
}

bool Window::Run()
{
	if (CoreInit() == false)
	{
		CoreRelease();
		return false;
	}

	MSG msg = { 0, };
	_bGameRun = true;

	_fGameTimer = 0.0f;
	_fElapseTimer = 10.0f;

	DWORD dwBeforeTime = timeGetTime();
	UINT fps = 0;
	UINT counter = 0;
	float fFps = 0.0f;
	while (_bGameRun)
	{
		if (WM_QUIT == msg.message)
		{
			break;
		}

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (!CoreFrame() || CoreRender())
			{
				_bGameRun = false;
			}
		}
		DWORD dwCurrentTime = timeGetTime();
		DWORD dwElapseTime = dwCurrentTime - dwBeforeTime;
		_fElapseTimer = dwElapseTime / 1000.0f;
		_fGameTimer += _fElapseTimer;
		std::wstring timer = std::to_wstring(_fGameTimer);
		dwBeforeTime = dwCurrentTime;

		counter++;
		fFps += _fElapseTimer;
		if (fFps >= 1.0f)
		{
			fps = counter;
			counter = 0;
			fFps = fFps - 1.0f;
		}
		timer += L" ";
		timer += std::to_wstring(fps);
		timer += L"\n";
		OutputDebugString(timer.c_str());
	}
	CoreRelease();

	return false;
}

void Window::CenterWIndow()
{
	UINT iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	UINT iScreenHieght = GetSystemMetrics(SM_CYFULLSCREEN);
	UINT cx, cy;
	cx = (iScreenWidth - (_rtWIndow.right - _rtWIndow.left)) * 0.5f;
	cy = (iScreenHieght - (_rtWIndow.bottom - _rtWIndow.top)) * 0.5f;
	MoveWindow(_hWnd, cx, cy, _rtWIndow.right - _rtWIndow.left, _rtWIndow.bottom - _rtWIndow.top, true);

}

bool Window::CoreInit()
{
	return false;
}

bool Window::CoreFrame()
{
	return false;
}

bool Window::CoreRender()
{
	return false;
}

bool Window::CoreRelease()
{
	return false;
}

LRESULT Window::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}

Window::Window()
{
	g_pWIndow = this;
}

Window::~Window()
{
}
