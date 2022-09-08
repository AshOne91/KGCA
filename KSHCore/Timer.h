#pragma once
#include "Std.h"
#pragma comment(lib, "winmm.lib") // timeGetTime
class Timer : public Singleton<Timer>
{
public:
	float _fGameTimer = 0.0f;
	float _fElapseTimer = 0.0f;
	UINT _iFPS = 0;
	std::wstring _szTimer;

private:
	DWORD _dwBeforeTime;
	UINT _iFPSCounter = 0;
	float _fFPSTimer = 0.0f;

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

#define I_Timer Timer::GetInstance()

