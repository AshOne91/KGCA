#include "Timer.h"

float g_fGameTimer = 0.0f;
float g_fSecondPerFrame = 0.0f;

bool Timer::Init()
{
    _fGameTimer = 0.0f;
    _fElapseTimer = 0.0f;
    _dwBeforeTime = timeGetTime(); //(1000: 1ÃÊ)
    return true;
}

bool Timer::Frame()
{
    DWORD dwCurrentTime = timeGetTime();
    DWORD dwElapseTime = dwCurrentTime - _dwBeforeTime;
    _fElapseTimer = dwElapseTime / 1000.0f;
    _fGameTimer += _fElapseTimer;
    {
        _iFPSCounter++;
        _fFPSTimer += _fElapseTimer;
        if (_fFPSTimer >= 1.0f)
        {
            _iFPS = _iFPSCounter;
            _iFPSCounter = 0;
            _fFPSTimer = _fFPSTimer - 1.0f;
        }
    }

    g_fGameTimer = _fGameTimer;
    g_fSecondPerFrame = _fElapseTimer;
    _dwBeforeTime = dwCurrentTime;
    return true;
}

bool Timer::Render()
{
    /*_szTimer = std::to_wstring(_fGameTimer);
    _szTimer += L"  ";
    _szTimer += std::to_wstring(_iFPS);
    _szTimer += L"\n";
    OutputDebugString(_szTimer.c_str());*/
    _szTimer = L"FPS:";
    _szTimer += std::to_wstring(_iFPS);
    return false;
}

bool Timer::Release()
{
    return false;
}
