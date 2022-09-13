#include "User2D.h"
#include "Input.h"

bool User2D::Frame()
{
    Vector2D vPos = _vPos;
    if (I_Input.GetKey('W'))
    {
        vPos.y += -1.0f * g_fSecondPerFrame * _fSpeed;
    }
    if (I_Input.GetKey('S'))
    {
        vPos.y += 1.0f * g_fSecondPerFrame * _fSpeed;
    }
    if (I_Input.GetKey('A'))
    {
        vPos.x += -1.0f * g_fSecondPerFrame * _fSpeed;
    }
    if (I_Input.GetKey('D'))
    {
        vPos.x += 1.0f * g_fSecondPerFrame * _fSpeed;
    }

    SetPosition(vPos);
	return true;
}
