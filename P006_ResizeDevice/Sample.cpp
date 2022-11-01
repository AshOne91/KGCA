#include "Sample.h"

bool Sample::Init()
{
	if (FAILED(InitDevice(m_hWnd, m_iWindowWidth, m_iWindowHeight, m_IsFullScreenMode)))
	{
		MessageBox(0, _T("CreateDevice  실패"), _T("Fatal error"), MB_OK);
		return false;
	}
	return true;
}
bool Sample::Render()
{	
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red,green,blue,alpha
	m_pImmediateContext->ClearRenderTargetView( m_pRenderTargetView, ClearColor );
	
	m_pSwapChain->Present( 0, 0 );
	return true;
}
bool Sample::Release()
{	
	if( !CleanupDevice() ) return false;	
	return true;
}
Sample::Sample(void)
{
}

Sample::~Sample(void)
{
}

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	Sample gSample;
	if( !gSample.InitWindow( hInstance, nCmdShow,  L"ResizeDivice" ) )
	{
		MessageBox( 0, _T("Sample  초기화 실패"), _T("Fatal error"), MB_OK );
		return 0;
	}	
	ShowCursor ( TRUE );
	gSample.Run();	
	return 1;
}