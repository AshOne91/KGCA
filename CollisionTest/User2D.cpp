#include "User2D.h"
#include "Input.h"
bool User2D::Frame()
{
    Vector2D vPos = _vPos;

    _vDir = { 0,0 };
    if (I_Input.GetKey('W'))
    {
        _vDir.y = -1.0f;
        vPos.y += -1.0f * g_fSecondPerFrame * _fSpeed;
    }
    if (I_Input.GetKey('S'))
    {
        _vDir.y = 1.0f;
        vPos.y += 1.0f * g_fSecondPerFrame * _fSpeed;
    }
    if (I_Input.GetKey('A'))
    {
        _vDir.x = -1.0f;
        vPos.x += -1.0f * g_fSecondPerFrame * _fSpeed;
    }
    if (I_Input.GetKey('D'))
    {
        _vDir.x = 1.0f;
        vPos.x += 1.0f * g_fSecondPerFrame * _fSpeed;
    }
    _vPos = vPos;
    return true;
}