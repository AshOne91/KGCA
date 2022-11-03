#include "AshWindow.h"

AshWindow* g_pWindow = nullptr;

namespace AshBASIS
{
	HWND _hWnd;
	HINSTANCE _hInstance;
	RECT _rtClient;
};

// ���� ������ ���ν���
LRESULT WINAPI StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	assert(g_pWindow);
	return g_pWindow->WindowMsgProc(hWnd, msg, wParam, lParam);
}

// �����Լ� ������ ���ν���
int AshWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return -1;
}

LRESULT AshWindow::WindowMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int iReturn = WndProc(hWnd, msg, wParam, lParam);
	if (iReturn >= 0)
	{
		return iReturn;
	}

	switch (msg)
	{
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case '0':
				{
					if (GetSwapChain())
					{
						BOOL IsScreenMode = FALSE;
						GetSwapChain()->GetFullscreenState(&IsScreenMode, NULL);
						GetSwapChain()->SetFullscreenState(!IsScreenMode, NULL);
						SetFullScreenFlag(IsScreenMode);
						assert(GetFullScreenFlag() == IsScreenMode);
						if (IsScreenMode)
						{
							ShowWIndow(hWnd, SW_SHOW);
						}
					}
				}
				break;
			}
		}
		case WM_SIZE :
		{
			if (SIZE_MINIMIZED != wParam) //�ּ�ȭ
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				//���� �������� ��ü��ǥ
				GetWindowRect(_hWnd, &_rcWindowBounds);
				//������ ��ü ��������
				GetClientRect(_hWnd, &_rcWindowClient);
				g_rtClient = _rcWindowClient;
				if (FAILED(ResizeDevice(width, height)))
				{
				}
			}
		}
		break;
		case WM_CLOSE :
		{
			HMENU hMenu;
			hMenu = GetMenu(hWnd);
			if (hMenu != NULL)
			{
				DestroyMenu(hMenu);
			}
			DestroyWindow(hWnd);
			UnregisterClass(TEXT("Ash Sample"), NULL);
			return 0;
		}
		break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool AshWindow::InitWIndow(HINSTANCE hInstance, int nCmdShow, const TCHAR* strWindowTitle = TEXT("Ash Sample"), int iWidth = 800, int iHeight = 600, BOOL IsFullScreen = FALSE)
{

}

// ������ ��ġ ȭ�� �߾����� �̵�
void AshWindow::CenterWindow(HWND hWnd)
{
	// �⺻ ���÷��� ������� ��ü ȭ�� â�� ���� Ŭ���̾�Ʈ ���� �ʺ�(�ȼ�)�Դϴ�.
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	// ����
	int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

	// do the centering math
	int iDestX = (iScreenWidth - (_rcWindowBounds.right - _rcWindowBounds.left)) / 2;
	int iDestY = (iScreenHeight - (_rcWindowBounds.bottom - _rcWindowBounds.top)) / 2;

	MoveWindow(hWnd, iDestX, iDestY, _rcWindowBounds.right - _rcWindowBounds.left, _rcWindowBounds.bottom - _rcWindowBounds.top, true);
}

bool AshWindow::CheckWindowSize()
{

}





AshWindow::AshWindow(void)
{
	_hInstance = NULL;
	_hWnd = NULL;
	g_pWindow = this;
}

AshWindow::~AshWindow(void)
{

}
