#include ".\tinput.h"

#define KEYDOWN(key)	(((m_KeyState[key]) & 0x80) ? true : false)
#define KEYUP(key)		(((m_KeyState[key]) & 0x80) ? false : true)

bool	TInput::ResetDevice()
{
	Release();
	Init();
	return true;
}
bool TInput::Render()
{
	return true;
}

bool TInput::Init()
{
	memset( &m_KeyBeforeState, 0, sizeof(BYTE) * KEYSTATECOUNT);
	memset( &m_MouseBeforeState, 0, sizeof(DIMOUSESTATE));
	m_dwElements = 0;
	return true;
}
bool TInput::Frame()
{
	if(!KeyProcess() || !MouseProcess() )
	{
		return false;
	}
	return true;
}

bool TInput::IsKeyDown( DWORD dwKey )
{
	if(m_dwImmediate)
	{
		if( KEYDOWN( dwKey ) ) 		return true;	
	}
	else
	{
		for( DWORD i = 0; i < m_dwElements; i++ ) 
		{
			// this will display then scan code of the key
			// plus a 'D' - meaning the key was pressed 
			//   or a 'U' - meaning the key was released
			// DOWN
			if( m_didod[ i ].dwOfs == dwKey && (m_didod[ i ].dwData & 0x80) )
			{
				return true;
			}		   
		}
	}	
	return false;
}
bool TInput::IsKeyUP( DWORD dwKey )
{
	if(m_dwImmediate)
	{
		if(m_KeyBeforeState[dwKey] & 0x80 ) 	
		{
			if( KEYUP( dwKey ) )
				return true;
		}
	}
	else
	{
		for( DWORD i = 0; i < m_dwElements; i++ ) 
		{
			// this will display then scan code of the key
			// plus a 'D' - meaning the key was pressed 
			//   or a 'U' - meaning the key was released	
			if( m_didod[ i ].dwOfs == dwKey && !(m_didod[ i ].dwData & 0x80) )
			{
				return true;
			}       
		}
	}

	
	return false;
}
void TInput::PostProcess()
{	
	memcpy( &m_KeyBeforeState, &m_KeyState, sizeof(BYTE) * KEYSTATECOUNT);
	memcpy( &m_MouseBeforeState, &m_MouseState, sizeof(DIMOUSESTATE));
}
TInput::TInput()
{
	m_pDi = NULL;
	m_pDidevKey = NULL;
	m_pDidevMouse = NULL;
	m_hWnd = NULL;
	m_dwElements= 0;
	m_dwImmediate = TRUE;
}

TInput::~TInput()
{
	Release();
}

bool TInput::InitDirectInput(HINSTANCE hInst, HWND hWnd, bool keyboard, bool mouse)
{
	HRESULT hr;//GetModuleHandle(NULL)
	m_hWnd = hWnd;
	if( m_pDidevKey || m_pDidevMouse ) return true;
	if(FAILED(hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDi, NULL)))
	{		
		return false;
	}

	if(keyboard)
	{
		if(FAILED(m_pDi->CreateDevice(GUID_SysKeyboard, &m_pDidevKey, NULL)))
			return false;
		if(FAILED(m_pDidevKey->SetDataFormat(&c_dfDIKeyboard)))
			return false;
		if(FAILED( hr = m_pDidevKey->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY)))
		{
			while(m_pDidevKey->Acquire() == DIERR_INPUTLOST);
			if(FAILED(m_pDidevKey->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_BACKGROUND | DISCL_NOWINKEY)))
				return false;
		}	
		if( !m_dwImmediate)
		{
			DIPROPDWORD dipdw;

			dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
			dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
			dipdw.diph.dwObj        = 0;
			dipdw.diph.dwHow        = DIPH_DEVICE;
			dipdw.dwData            = SAMPLE_BUFFER_SIZE; // Arbitary buffer size

			if( FAILED( hr = m_pDidevKey->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph ) ) )
				return false;
		}

		while(m_pDidevKey->Acquire() == DIERR_INPUTLOST);
	}
	if(mouse)
	{
		if(FAILED(m_pDi->CreateDevice(GUID_SysMouse, &m_pDidevMouse, NULL)))
			return false;
		if(FAILED(m_pDidevMouse->SetDataFormat(&c_dfDIMouse)))
			return false;
		if(FAILED(m_pDidevMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE |DISCL_BACKGROUND)))
		{
			while(m_pDidevMouse->Acquire() == DIERR_INPUTLOST);
			if(FAILED(m_pDidevMouse->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE |  DISCL_FOREGROUND)))
				return false;

		}
		while(m_pDidevMouse->Acquire() == DIERR_INPUTLOST);
	}

	return true;
}

bool TInput::Release()
{
	if(m_pDi)
	{
		if(m_pDidevKey)
		{
			m_pDidevKey->Unacquire();
			m_pDidevKey->Release();
			m_pDidevKey = NULL;
		}
		if(m_pDidevMouse)
		{
			m_pDidevMouse->Unacquire();
			m_pDidevMouse->Release();
			m_pDidevMouse = NULL;
		}

		m_pDi->Release();
		m_pDi = NULL;
	}
	return true;
}

bool TInput::KeyProcess()
{
	HRESULT            hr;
	if(m_dwImmediate)
	{
		ZeroMemory(m_KeyState, sizeof(BYTE)*KEYSTATECOUNT);
		if(!m_pDidevKey) return false;
		if(FAILED(m_pDidevKey->GetDeviceState(KEYSTATECOUNT, m_KeyState)))
		{
			while(m_pDidevKey->Acquire() == DIERR_INPUTLOST)
				m_pDidevKey->Acquire();
			return true;
		}
	}
	else
	{	
		if( NULL == m_pDidevKey )     return false;
		memset(&m_didod, 0, sizeof(DIDEVICEOBJECTDATA)* SAMPLE_BUFFER_SIZE);
		m_dwElements = SAMPLE_BUFFER_SIZE;
		hr = m_pDidevKey->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), m_didod, &m_dwElements, 0 );

		if( hr != DI_OK ) 
		{
			m_dwElements= 0;
			hr = m_pDidevKey->Acquire();
			while( hr == DIERR_INPUTLOST ) 
				hr = m_pDidevKey->Acquire();
			return true; 
		}
	}
	return true;
}

bool TInput::MouseProcess()
{
	ZeroMemory(&m_MouseState, sizeof(DIMOUSESTATE));
    if( !m_pDidevMouse ) return false;
	
	if(FAILED(m_pDidevMouse->GetDeviceState(sizeof(DIMOUSESTATE),&m_MouseState)))
	{		
		while(m_pDidevMouse->Acquire() == DIERR_INPUTLOST)
			m_pDidevMouse->Acquire();

		return true;
	}

	return true;
}
void TInput::SetAcquire(bool bActive)
{
	if( bActive ) DeviceAcquire();
	else		  DeviceUnacquire();	
}
void TInput::DeviceAcquire()
{
	if(m_pDidevKey)
		m_pDidevKey->Acquire();
	if(m_pDidevMouse)
		m_pDidevMouse->Acquire();
}

void TInput::DeviceUnacquire()
{
	if(m_pDidevKey)
		m_pDidevKey->Unacquire();
	if(m_pDidevMouse)
		m_pDidevMouse->Unacquire();
}

