#pragma once
#include "Std.h"

class Window
{
public:
	HINSTANCE _hInstance;
	HWND _hWnd;
	RECT _rtWIndow;
	RECT _rtClient;
	DWORD _csStyle;
	UINT _iClientWidth;
	UINT _iClientHeight;

public:
	bool SetWindow(HINSTANCE hInst, const TCHAR* szTitle, UINT iWidth = 1024, UINT iHeight = 768);
	ATOM MyRegisterClass();
	BOOL InitInstance(const TCHAR* szTitle, UINT iWidth, UINT iHeight);
	virtual bool Run();
	void CenterWIndow();
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	Window();
	virtual ~Window();
};