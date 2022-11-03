#pragma once
#include "TWindow.h"
#include "TDirectWrite.h"
#include "TTimer.h"
class Sample : public TWindow
{
public:
	TDirectWrite		m_Font;
	IDXGISurface1*		m_pBackBuffer;
	TTimer				m_Timer;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	HRESULT		ResizeDevice( UINT iWidth, UINT iHeight);
public:
	Sample(void);
	~Sample(void);
};
