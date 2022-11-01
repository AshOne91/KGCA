#include "Sample.h"

bool Sample::Init()
{	
	TDevice::CreateGIFactory();
	// ─────────────────────────────────
	// 
	// ─────────────────────────────────
	FILE	*fp;
	fp = _tfopen( _T("DeviceInfo.txt"),_T("wt") );
	if( !fp )
	{
		MessageBox(NULL, _T("파일을 생성하지 못했습니다."), _T("파일생성에러"), MB_ICONERROR);
		return FALSE;
	}
	TEnumAdapter* pAdapterInfo;
	_ftprintf( fp, L"Num Adapter : %d\n", m_Enumeration.m_AdapterInfoList.size());	

    for( int i = 0; i < m_Enumeration.m_AdapterInfoList.size(); i++ )
    {
        pAdapterInfo = m_Enumeration.m_AdapterInfoList[i];		
		_ftprintf( fp, L"Description[%d] : %s,  Num Output:%d\n", i, pAdapterInfo->m_AdapterDesc.Description, 
											  pAdapterInfo->m_OutputInfoList.size());	
		
		TEnumOutput* pOutputInfo;
		for( int i = 0; i < pAdapterInfo->m_OutputInfoList.size(); i++ )
		{
			pOutputInfo = pAdapterInfo->m_OutputInfoList[i];
			_ftprintf( fp, L"\n\tOutput[%d] m_Desc:%s\t DesktopCoordinates:%d,%d,%d,%d : NumDisplayMode:%d\t\n",	i,pOutputInfo->m_Desc.DeviceName,
										pOutputInfo->m_Desc.DesktopCoordinates.left,
										pOutputInfo->m_Desc.DesktopCoordinates.top,
										pOutputInfo->m_Desc.DesktopCoordinates.right,
										pOutputInfo->m_Desc.DesktopCoordinates.bottom,
										pOutputInfo->m_DisplayModeList.size() );
			
			// 연장시는 left:1680, right == 3360;
			
			DXGI_MODE_DESC* pModeDesc;
			for( int i = 0; i < pOutputInfo->m_DisplayModeList.size(); i++ )
			{
				pModeDesc = &pOutputInfo->m_DisplayModeList[i];
				_ftprintf( fp, L"\t\tDisplayMode[%d] Width:%d height:%d FORMAT:%d RefreshRate:%d-%d\t\n",	i,
											pModeDesc->Width, pModeDesc->Height,
											pModeDesc->Format,
											pModeDesc->RefreshRate.Numerator, pModeDesc->RefreshRate.Denominator );
			}
		}
    }
	
	fclose( fp );
	MessageBox(NULL, _T("DeviceInfo.txt 파일을 성공적으로 생성하였습니다."), _T("파일생성"), MB_OK);	

	HRESULT hr;
	T_RETURN(CreateDevice(), false);
	T_RETURN(CreateSwapChain(m_hWnd, this->m_iWindowWidth, this->m_iWindowHeight), false);
	T_RETURN(SetRenderTargetView(), false);
	T_RETURN(SetViewPort(), false);
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
	if( !gSample.InitWindow( hInstance, nCmdShow,  L"DXGI Information" ) )
	{
		MessageBox( 0, _T("Sample  초기화 실패"), _T("Fatal error"), MB_OK );
		return 0;
	}	
	ShowCursor ( TRUE );
	gSample.Run();	
	return 1;
}