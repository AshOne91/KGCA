#pragma once
#include <Windows.h>

class AshWindow
{
public:
	HINSTANCE _hInstance; // 인스턴스 핸들
	HWND _hWnd; // 윈도우 핸들
	DWORD _dwWIndowStyle; // 윈도우 스타일
	RECT _rcWindowBounds; // 윈도우 영역
	RECT _rcWindowClient; // 클라이언트 영역
	UINT _iWindowWidth; // 클라이언트 영역 가로크기
	UINT _iWindowHeight; // 클라이언트 영역 세로크기

public:
	bool InitWIndow(HINSTANCE hInstance, int nCmdShow, const TCHAR* strWindowTitle = TEXT("Ash Sample"), int iWidth = 800, int iHeight = 600, BOOL IsFullScreen = FALSE);
	// 윈도우 위치 화면 중앙으로 이동
	void CenterWindow(HWND hWnd);
	bool CheckWindowSize();

public:
	virtual int WndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT WindowMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	AshWindow(void);
	virtual ~AshWindow(void);

};

