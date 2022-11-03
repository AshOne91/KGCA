#pragma once
#include <Windows.h>

class AshWindow
{
public:
	HINSTANCE _hInstance; // �ν��Ͻ� �ڵ�
	HWND _hWnd; // ������ �ڵ�
	DWORD _dwWIndowStyle; // ������ ��Ÿ��
	RECT _rcWindowBounds; // ������ ����
	RECT _rcWindowClient; // Ŭ���̾�Ʈ ����
	UINT _iWindowWidth; // Ŭ���̾�Ʈ ���� ����ũ��
	UINT _iWindowHeight; // Ŭ���̾�Ʈ ���� ����ũ��

public:
	bool InitWIndow(HINSTANCE hInstance, int nCmdShow, const TCHAR* strWindowTitle = TEXT("Ash Sample"), int iWidth = 800, int iHeight = 600, BOOL IsFullScreen = FALSE);
	// ������ ��ġ ȭ�� �߾����� �̵�
	void CenterWindow(HWND hWnd);
	bool CheckWindowSize();

public:
	virtual int WndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT WindowMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	AshWindow(void);
	virtual ~AshWindow(void);

};

