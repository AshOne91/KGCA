#include "Sample.h"
typedef basic_string<TCHAR>				T_STR;

bool Sample::Init()
{	
	if( FAILED( InitDevice(m_hWnd,this->m_iWindowWidth, this->m_iWindowHeight) ) )
	{
		MessageBox( 0, _T("CreateDevice  실패"), _T("Fatal error"), MB_OK );
		return false;
	}

	if( !m_Timer.Init() )	return false;
	m_Timer.Start();

	IDXGISurface1*		pBackBuffer=NULL;
	HRESULT hr = GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (LPVOID*)&pBackBuffer);	
	m_Font.Set(m_hWnd, m_iWindowWidth, m_iWindowHeight, pBackBuffer );		
	if( pBackBuffer )	pBackBuffer->Release();

	/*if(!m_Font.Init())
	{
		return false;
	}
	if(!m_Font.Set(m_pd3dDevice, m_pImmediateContext))
	{
		return false;
	}*/
	// DirectX Input 생성 
	if( !I_Input.InitDirectInput( m_hInstance , m_hWnd, true, true ) )
	{
		return false;
	}

	// DirectX Input 초기화
	if( !I_Input.Init() )
	{
		return false;
	}
	return true;
}
bool Sample::Release()
{	
	m_Timer.Stop();
	if( !CleanupDevice() ) return false;	
	if( !m_Timer.Release() ) return false;		
	if( !m_Font.Release() ) return false;		
	if( !I_Input.Release() ) return false;	
	return true;
}
bool  Sample::Frame()
{
	if( !m_Timer.Frame() ) return false;
	static float fTimer = 0.0f;
	fTimer  += m_Timer.GetSPF();
	//if( !I_Input.m_dwImmediate &&  fTimer > 0.2f )
	{
		//m_strBuffer.clear();
		if( !I_Input.Frame() ) return false;
		fTimer = 0.0f;
	}	
	return true;
}

bool Sample::Render()
{
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red,green,blue,alpha
	m_pImmediateContext->ClearRenderTargetView( m_pRenderTargetView, ClearColor );
	
	

	TCHAR pBuffer[256];
	memset( pBuffer, 0, sizeof( TCHAR ) * 256 );

	
	
	// 인풋 정보 출력
	int iCount = 0;
	if( I_Input.m_dwImmediate )
	{
		for( int iKey = 0; iKey < KEYSTATECOUNT; iKey++ )
		{
			if(	I_Input.m_KeyState[iKey] & 0x80 )
			{         
				// DirectInput keyboard scan codes
				_stprintf_s( pBuffer, _T("Key State:0x%02x : %d"), iKey, I_Input.m_KeyState[iKey] );		
				UINT iStartX = m_iWindowWidth/2;
				UINT iStartY = m_iWindowHeight/2+( 20*iCount);				

				m_Font.Begin();
					m_Font.m_pRT->SetTransform(D2D1::Matrix3x2F::Identity());
					m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
					RECT rc1 = {iStartX,iStartY, m_iWindowWidth, m_iWindowHeight};
					m_Font.DrawText(rc1, pBuffer,  D2D1::ColorF(1,1,1,0.5));
				m_Font.End();

			/*	m_Font.Begin();
					m_Font.DrawTextLine( pBuffer, iStartX, iStartY);	
				m_Font.End();*/
				iCount++;
			}
		}
	}
	else
	{	
		//2
		int iCount = I_Input.m_dwElements;
		if( iCount >= 1  ) m_strBuffer.clear();
		for( DWORD i = 0; i < iCount; i++ ) 
		{				
			_stprintf_s( pBuffer, _T("Key[%d] State:0x%02x %s \n"),i,  I_Input.m_didod[ i ].dwOfs,
									( I_Input.m_didod[ i ].dwData & 0x80 ) ? TEXT( "Down" ) : TEXT( "Up" ) );								
			m_strBuffer += pBuffer;
		}		
		
		
			UINT iStartX = 0;
			UINT iStartY = 0;	

			m_Font.Begin();
					m_Font.m_pRT->SetTransform(D2D1::Matrix3x2F::Identity());
					m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
					RECT rc1 = {iStartX,iStartY, m_iWindowWidth, m_iWindowHeight};
					const TCHAR* strData = m_strBuffer.c_str();
					m_Font.DrawText(rc1, const_cast<TCHAR*>(strData),  D2D1::ColorF(1,1,1,0.5));
			m_Font.End();
		
/*
		m_Font.Begin();
					m_Font.DrawTextLine( strBuffer.c_str(), iStartX, iStartY);	
		m_Font.End();*/
	}	
	

	for( int iKey = 0; iKey < 4; iKey++ )
	{
		if(	I_Input.m_MouseState.rgbButtons[iKey] & 0x80 )
        {         
			_stprintf_s( pBuffer, _T("Mouse Button State:%02d"), iKey );		
			UINT iStartX = m_iWindowWidth/2;
			UINT iStartY = m_iWindowHeight/2+( 20*iCount);		

			m_Font.Begin();
				m_Font.m_pRT->SetTransform(D2D1::Matrix3x2F::Identity());
				m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				RECT rc1 = {iStartX,iStartY, m_iWindowWidth, m_iWindowHeight};
				m_Font.DrawText(rc1, pBuffer,  D2D1::ColorF(1,1,1,0.5));
			m_Font.End();

			/*m_Font.Begin();
					m_Font.DrawTextLine( pBuffer, iStartX, iStartY);	
			m_Font.End();*/
			iCount++;
		}
	}

	static LONG MousePosX = I_Input.m_MouseState.lX;
	static LONG MousePosY = I_Input.m_MouseState.lY;
	static LONG MousePosZ = I_Input.m_MouseState.lZ;	
	MousePosX += I_Input.m_MouseState.lX;
	MousePosY += I_Input.m_MouseState.lY;
	MousePosZ += I_Input.m_MouseState.lZ;
	_stprintf_s( pBuffer, _T("Mouse X:%ld,Y:%ld,Z:%ld"),	 MousePosX, 
															 MousePosY,
															 MousePosZ);	
	UINT iStartX = m_iWindowWidth/2;
	UINT iStartY = m_iWindowHeight/2+( 20*iCount);
	m_Font.Begin();
				D2D1_POINT_2F center;
				center.x = 0;
				center.y = 0;
				m_fScale = 1.0f + cosf(m_Timer.GetElapsedTime())*0.5f + 0.5f;
				D2D1::Matrix3x2F scale = D2D1::Matrix3x2F::Scale(m_fScale, m_fScale);
				D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(m_Timer.GetElapsedTime()*100.0f, center);
				D2D1::Matrix3x2F trans = D2D1::Matrix3x2F::Translation(iStartX, iStartY);
				m_matWorld = scale * rot * trans;
				m_Font.m_pRT->SetTransform(m_matWorld);
				m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				RECT rc1 = {0,0, m_iWindowWidth, m_iWindowHeight};
				m_Font.DrawText(rc1, pBuffer,  D2D1::ColorF(1,1,1,0.5));
	m_Font.End();
	/*m_Font.Begin();
		m_Font.DrawTextLine( pBuffer, iStartX, iStartY);	
	m_Font.End();*/
	// 타이머 정보 출력
	memset( pBuffer, 0, sizeof( TCHAR ) * 256 );	
	_stprintf_s( pBuffer, _T("FPS:%d SecPerFrame:%10.5f Elapsed : %10.2f"),	m_Timer.GetFPS(), 
																			m_Timer.GetSPF(),
																			m_Timer.GetElapsedTime());		
	iStartX = m_iWindowWidth;
	iStartY = 0;
	m_Font.Begin();	
				m_Font.m_pRT->SetTransform(D2D1::Matrix3x2F::Identity());
				m_Font.m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				m_Font.m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				RECT rc2 = {iStartX,iStartY, m_iWindowWidth, m_iWindowHeight};
				m_Font.DrawText(rc2, pBuffer,  D2D1::ColorF(1,1,1,0.5));
	m_Font.End();
	//m_Font.Begin();
	//	m_Font.DrawTextLine( pBuffer, iStartX, iStartY);	
	//m_Font.End();

	m_pSwapChain->Present( 0, 0 );
	I_Input.PostProcess();
	return true;
}	
Sample::Sample(void)
{
	m_matWorld = D2D1::IdentityMatrix();
	m_fScale = 1.0f;
}

Sample::~Sample(void)
{
}

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
	Sample gSample;
	if( !gSample.InitWindow( hInstance, nCmdShow,  L"DirectX Input" ) )
	{
		MessageBox( 0, _T("Sample  초기화 실패"), _T("Fatal error"), MB_OK );
		return 0;
	}	
	ShowCursor ( TRUE );
	gSample.Run();	
	return 1;
}


