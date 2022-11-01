#pragma once
#include "TWindow.h"
#include "TTimer.h"
#include "TDirectWrite.h"

class Sample : public TWindow
{
public:
	TTimer				m_Timer;
	TDirectWrite		m_Font;
	IDXGISurface1*		m_pBackBuffer;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	HRESULT		ResizeDevice(UINT iWidth, UINT iHeight);
public:
	Sample(void);
	~Sample(void);
};
