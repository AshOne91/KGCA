#pragma once
#include <Windows.h>
class TWindow
{
public:
	HINSTANCE m_hInstance;
public:
	ATOM MyRegisterClass();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	BOOL InitInstance();
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Run();
};

