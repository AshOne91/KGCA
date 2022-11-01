#pragma once
#include "TDevice.h"

class TWindow : public TDevice
{
public:
	//--------------------------------------------------------------------------------------
	// Global Variables
	//--------------------------------------------------------------------------------------
	HINSTANCE               m_hInstance;		// 인스턴스 핸들
	HWND                    m_hWnd;				// 윈도우 핸들
	DWORD					m_dwWindowStyle;	// 윈도우 스타일
	RECT					m_rcWindowBounds;   // 윈도우 영역
	RECT					m_rcWindowClient;   // 클라이언트 영역	
	UINT					m_iWindowWidth;		// 클라이언트 영역 가로크기
	UINT					m_iWindowHeight;	// 클라이언트 영역 세로크기
	bool					m_bResizeDrag;		// 윈도우 크기변경 드래그 시작 여부
public:
	// 윈도우 생성
	bool				InitWindow(HINSTANCE hInstance, int nCmdShow, CONST TCHAR* strWindowTitle, BOOL IsFullScreen = FALSE);
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
	TWindow(void);
	virtual ~TWindow(void);
};
