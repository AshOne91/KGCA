#pragma once
#include <windows.h>
#include <assert.h>
#include <tchar.h>
#include <d3d11.h>
#include <dxgi.h> 
#include <set>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <bitset>
#include <limits>
#include <functional>
using namespace std;

//#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "dxgi.lib" )

//#if defined(DEBUG) || defined(_DEBUG)	
//	#pragma comment( lib, "d3dx11d.lib" )	
//#else	
//	#pragma comment( lib, "d3dx11.lib" )
//#endif

#pragma comment( lib, "d3dcompiler.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "comctl32.lib" )


typedef basic_string<TCHAR>				T_STR;
typedef basic_string<TCHAR>::iterator	T_ITOR;

typedef vector<basic_string<TCHAR>>	T_STR_VECTOR;
typedef vector<string>				C_STR_VECTOR;

typedef list<basic_string<TCHAR>>	T_STR_LIST;
typedef string						CHAR_STRING;

typedef vector<DWORD>				DWORD_VECTOR;
typedef	vector< DWORD >::iterator	DWORD_VECTOR_ITOR;

typedef list<DWORD>					DWORD_LIST;
typedef list<DWORD>::iterator		DWORD_LIST_ITOR;

typedef list< HANDLE >				HANDLE_LIST;
typedef	list< HANDLE >::iterator	HANDLE_LIST_ITOR;

extern HWND g_hWnd;
extern RECT  g_rtClient;
extern float g_fGameTimer;
extern float g_fSecPerFrame;
//////////////////////////////////////////////
// DX �żҵ� ȣ�⿡ ���� ��ȯ�� ó�� ��ũ��
//////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////////////////////////
// ����� �޼���( ������ ����Ǵ� ������ ����� ) : ���ϸ�� ���� �� ���ڿ��� ��µǸ� ���� �����.
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define	DEBUGMSG(lpText)															\
	{																						\
		TCHAR szBuffer[256];															\
		_stprintf_s(szBuffer, _T("[File: %s][Line: %d]\n[Note : %s]"), __FILE__, __LINE__, lpText);	\
		MessageBox(NULL, szBuffer, _T("ERROR"), MB_ICONERROR);									\
		_ASSERT(1);																			\
		_asm {																				\
		int 3																			\
		}																					\
	}
#else
#define DEBUGMSG(lpText)
#endif
//////////////////////////////////////////////
// ��ü �� �迭 �Ҵ�� ���� �� �Ҹ� ��ũ��
//////////////////////////////////////////////
#ifndef SAFE_ZERO
	#define SAFE_ZERO(A)				{ A = 0; }
#endif

#ifndef SAFE_NEW
	#define SAFE_NEW(A, B)				{ if (!A) A = new B; }
#endif 

#ifndef SAFE_DEL
	#define SAFE_DEL(A)					{ if (A) delete A; (A)=NULL; }
#endif 

#ifndef SAFE_NEW_ARRAY
	#define SAFE_NEW_ARRAY(A, B, C)		{ if (!A && C) A = new B[C]; }
#endif 

#ifndef SAFE_DELETE_ARRAY
	#define SAFE_DELETE_ARRAY(A)		{ if (A) delete [] A; (A)=NULL; }
#endif 

#ifndef SAFE_RELEASE
	#define SAFE_RELEASE(A)				{ if(A) { (A)->Release(); (A)=NULL; } }
#endif 

#ifndef SAFE_NEW_CLEAR
	#define SAFE_NEW_CLEAR( A, B )			{ if (!A) A = new B; if(A) memset( A, 0, sizeof(B) ); };
#endif 

#ifndef SAFE_NEW_ARRAY_CLEAR
	#define NEW_ARRAY_CLEAR( A, B, C )	{ if (!A && C) A = new B[C]; if(A) memset( A, 0, sizeof(B)*C ); };
#endif

