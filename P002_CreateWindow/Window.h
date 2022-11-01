#pragma once
#include <Windows.h>
#include <assert.h>
#include <tchar.h>

class Window
{
public:
	HINSTANCE               _hInstance;		// �ν��Ͻ� �ڵ�
	HWND                    _hWnd;				// ������ �ڵ�
	DWORD					_dwWindowStyle;	// ������ ��Ÿ��
	RECT					_rcWindowBounds;   // ������ ����
	RECT					_rcWindowClient;   // Ŭ���̾�Ʈ ����	
	UINT					_iWindowWidth;		// Ŭ���̾�Ʈ ���� ����ũ��
	UINT					_iWindowHeight;	// �����̾�Ʈ ���� ����ũ��

public:
	// ������ ����
	bool				InitWindow(HINSTANCE hInstance, int nCmdShow, CONST TCHAR* strWindowTitle);
	// ������ ��ġ ȭ�� �߾����� �̵�
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

