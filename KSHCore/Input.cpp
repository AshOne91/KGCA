#include "Input.h"

bool Input::Init()
{
    ZeroMemory(_dwKeyState, sizeof(DWORD) * 256);
    GetCursorPos(&_ptPos);
    ScreenToClient(g_hWnd, &_ptPos);
    _ptPrePos = _ptPos;
    return true;
}

bool Input::Frame()
{
    GetCursorPos(&_ptPos);
    ScreenToClient(g_hWnd, &_ptPos);
    _ptOffset.x = _ptPos.x - _ptPrePos.x;
    _ptOffset.y = _ptPos.y - _ptPrePos.y;

    for (int iKey = 0; iKey < 256; ++iKey)
    {
        SHORT sKey = GetAsyncKeyState(iKey);
        if (sKey & 0x8000)
        {
            if (_dwKeyState[iKey] == KEY_FREE || _dwKeyState[iKey] == KEY_UP)
            {
                _dwKeyState[iKey] = KEY_PUSH;
            }
            else
            {
                _dwKeyState[iKey] = KEY_HOLD;
            }
        }
        else
        {
            if (_dwKeyState[iKey] == KEY_PUSH || _dwKeyState[iKey] == KEY_HOLD)
            {
                _dwKeyState[iKey] = KEY_UP;
            }
            else
            {
                _dwKeyState[iKey] = KEY_FREE;
            }
        }
    }
    _ptPrePos = _ptPos;
    return true;
}

bool Input::Render()
{
    return true;
}

bool Input::Release()
{
    return true;
}

DWORD Input::GetKey(DWORD dwKey)
{
    return _dwKeyState[dwKey];
}
