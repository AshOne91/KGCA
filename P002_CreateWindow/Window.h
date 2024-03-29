#pragma once
#include <Windows.h>
#include <assert.h>
#include <tchar.h>

class Window
{
public:
	HINSTANCE               _hInstance;		// 인스턴스 핸들
	HWND                    _hWnd;				// 윈도우 핸들
	DWORD					_dwWindowStyle;	// 윈도우 스타일
	RECT					_rcWindowBounds;   // 윈도우 영역
	RECT					_rcWindowClient;   // 클라이언트 영역	
	UINT					_iWindowWidth;		// 클라이언트 영역 가로크기
	UINT					_iWindowHeight;	// 을라이언트 영역 세로크기

public:
	// 윈도우 생성
	bool				InitWindow(HINSTANCE hInstance, int nCmdShow, CONST TCHAR* strWindowTitle);
	// 윈도우 위치 화면 중앙으로 이동
	void				CenterWindow(HWND hwnd);

public:
	virtual bool		Init();
	virtual	bool		Frame();
	virtual	bool		Render();
	virtual bool		Release();
	virtual	bool		Run();
	virtual LRESULT		WndProc(HWND, UINT, WPARAM, LPARAM);
public:
	Window(void);
	virtual ~Window(void);
};

