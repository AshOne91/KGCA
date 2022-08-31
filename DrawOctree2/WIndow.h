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
	bool _bGameRun;
	float _fGameTimer = 0.0f;
	float _fElapseTimer = 10.0f;
#ifdef _DEBUG
	std::vector<UINT> msglist;
#endif
public:
	bool SetWindow(HINSTANCE hInst, const TCHAR* szTitle, UINT iWidth = 1024, UINT iHeight = 768);
	ATOM MyRegisterClass();
	BOOL InitInstance(const TCHAR* szTitle, UINT iWidth, UINT iHeight);
	bool Run();
	void CenterWIndow();
public:
	virtual bool CoreInit();
	virtual bool CoreFrame();
	virtual bool CoreRender();
	virtual bool CoreRelease();
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	Window();
	virtual ~Window();
};