#pragma once
#include "TWindow.h"

class Sample : public TWindow
{
public:
	BOOL		m_IsFullScreenMode;
public:
	bool		Init();
	bool		Render();
	bool		Release();
	LRESULT		WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
public:
	Sample(void);
	~Sample(void);
};
