#pragma once
#include "TTemplate.h"

namespace TBASIS_BASE { 

class TInput : public TSingleton < TInput >
{
private:
	friend class TSingleton<TInput>;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	bool		ResetDevice();
	bool		ResetResource(){return true;};
public:
	LPDIRECTINPUT8			m_pDi;
	LPDIRECTINPUTDEVICE8	m_pDidevKey;
	LPDIRECTINPUTDEVICE8	m_pDidevMouse;
	DIDEVICEOBJECTDATA		m_didod[ SAMPLE_BUFFER_SIZE ];

	BYTE					m_KeyState[KEYSTATECOUNT];
	BYTE					m_KeyBeforeState[KEYSTATECOUNT];
	DIMOUSESTATE			m_MouseState;
	DIMOUSESTATE			m_MouseBeforeState;
	DWORD					m_dwElements;
	HWND					m_hWnd;
	DWORD					m_dwImmediate;
public:
	bool		InitDirectInput(HINSTANCE, HWND, bool, bool);
	bool		KeyProcess();
	bool		MouseProcess();
	void		DeviceAcquire();
	void		DeviceUnacquire();	
	bool		IsKeyDown( DWORD dwKey );
	bool		IsKeyUP( DWORD dwKey );
	void		PostProcess();
	void		SetAcquire(bool bActive);
public:
	TInput(void);
	virtual ~TInput(void);
};
#define I_Input TInput::GetInstance()
}
using namespace TBASIS_BASE;

