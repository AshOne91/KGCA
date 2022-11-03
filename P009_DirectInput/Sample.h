#pragma once
#include "TWindow.h"
#include "TTimer.h"
#include "TDirectWrite.h"
#include "TInput.h"

class Sample : public TWindow
{
public:
	TTimer				m_Timer;
	TDirectWrite		m_Font;
	T_STR				m_strBuffer;
	D2D1_MATRIX_3X2_F	m_matWorld;
	float				m_fScale;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
public:
	Sample(void);
	~Sample(void);
};
