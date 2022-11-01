#pragma once
#include <assert.h>
#include <tchar.h>
#include <d3d11.h>

#pragma comment		(lib, "dxgi.lib")
#pragma comment		(lib, "d3d11.lib")
//#pragma comment		(lib, "legacy_stdio_definitions.lib")

#define str(x) L#x
#define xstr(x) str(x)

/////////////////////////////////////////  ��ȯ���� �ʴ´�. ////////////////////////////////////////////////////////
#if defined(DEBUG) | defined(_DEBUG) 
#ifndef H
//���ǻ���:��ũ�� �Լ��ȿ��� ��ũ�� �Լ�(x�� �Լ��� �ؼ�)�� �ߺ� ���� ���� �ʰ� x=DX�޼ҵ常 ����ؾ� �Ѵ�.
#define H(x){ hr = (x);if (FAILED(hr)){\
							LPWSTR output;\
							WCHAR buffer[256]={0,};\
							FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS |FORMAT_MESSAGE_ALLOCATE_BUFFER,\
							NULL,x,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&output,0,NULL);\
							wsprintf(buffer,L"File=%s\nLine=%s", xstr(__FILE__),xstr(__LINE__));\
							MessageBox(NULL, buffer,output,MB_OK);}\
						}
#endif
#else
#ifndef H
#define H(x) (x)
#endif
#endif

/////////////////////////////////////////  ������ ��츸 ��ȯ�Ѵ� ////////////////////////////////////////////////////////
#if defined(DEBUG) | defined(_DEBUG) 
#ifndef H_RETURN
//���ǻ���:hr = (x); �� �־�� ��ũ�� �Լ��ȿ��� ��ũ�� �Լ�(x�� �Լ��� �ؼ�)�� �ߺ� �������� �ʴ´�.
#define H_RETURN(x){  hr = (x); if (FAILED(hr)){\
							LPWSTR output;\
							WCHAR buffer[256]={0,};\
							FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS |FORMAT_MESSAGE_ALLOCATE_BUFFER,\
							NULL,hr,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&output,0,NULL);\
							wsprintf(buffer,L"File=%s\nLine=%s", xstr(__FILE__),xstr(__LINE__));\
							MessageBox(NULL, buffer,output,MB_OK); return hr;}\
						}
#endif
#else
#define H_RETURN(x){ hr = (x); if( FAILED(hr) ) { return hr; }}
#endif

/////////////////////////////////////////  ������ ��ȯ�Ѵ� ////////////////////////////////////////////////////////
#if defined(DEBUG) | defined(_DEBUG) 
#ifndef U_RETURN
//���ǻ���:hr = (x); �� �־�� ��ũ�� �Լ��ȿ��� ��ũ�� �Լ�(x�� �Լ��� �ؼ�)�� �ߺ� �������� �ʴ´�.
#define U_RETURN(x){  hr = (x);if (FAILED(hr)){\
							LPWSTR output;\
							WCHAR buffer[256]={0,};\
							FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS |FORMAT_MESSAGE_ALLOCATE_BUFFER,\
							NULL,x,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&output,0,NULL);\
							wsprintf(buffer,L"File=%s\nLine=%s", xstr(__FILE__),xstr(__LINE__));\
							MessageBox(NULL, buffer,output,MB_OK); return hr;}\
							else { return hr;}\
						}
#endif
#else
#define U_RETURN(x){ hr = (x); return hr; }
#endif


#ifndef V
#define V(x)       { hr = (x); }
#endif
#ifndef V_RETURN
#define V_RETURN(x){ hr = (x); if( FAILED(hr) ) { return hr; } }
#endif
#ifndef T_RETURN
#define T_RETURN(x,ret){ hr = (x); if( FAILED(hr) ) { return ret; } }
#endif

class TDevice
{
public:
	//--------------------------------------------------------------------------------------
	// Global Variables
	//--------------------------------------------------------------------------------------	
	ID3D11Device* m_pd3dDevice;		// ����̽� ��ü
	IDXGISwapChain* m_pSwapChain;		// ����ü�� ��ü
	ID3D11RenderTargetView* m_pRenderTargetView;// ���� ����Ÿ�� ��
	D3D11_VIEWPORT			m_ViewPort;			// ����Ʈ 
	D3D_DRIVER_TYPE         m_driverType;		// ����̽� Ÿ��( ����Ʈ:�ϵ���� ���� )
	IDXGIFactory* m_pGIFactory;		// DXGI ��ü
	ID3D11DeviceContext* m_pImmediateContext;// ����̽� ���ؽ�Ʈ
	D3D_DRIVER_TYPE			m_DriverType;		// ����̽� Ÿ��
	D3D_FEATURE_LEVEL       m_FeatureLevel;		// DirectX�� ��ɼ���

public:
	//--------------------------------------------------------------------------------------
	// ����̽� �� ����ü�� ���� : 
	// 1, CreateDevice()
	// 2, CreateGIFactory()
	// 3, CreateSwapChain()
	// 4, SetRenderTargetView()
	// 5, SetViewPort()
	//--------------------------------------------------------------------------------------
	HRESULT		CreateDevice();
	HRESULT		CreateGIFactory();
	HRESULT		CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeigh);
	//--------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------
	HRESULT		SetRenderTargetView();
	HRESULT		SetViewPort();
	bool		CleanupDevice();

public:
	TDevice(void);
	virtual ~TDevice(void);
};
