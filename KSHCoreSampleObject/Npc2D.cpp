#include "Npc2D.h"

bool Npc2D::Frame()
{
    Vector2D vPos = _vPos;
    //벡터의 직선의 방정식 &  시간의 동기화
    Vector2D m_vVelocity = _vDir * _fSpeed * g_fSecondPerFrame;
    vPos = vPos + m_vVelocity;

    if (vPos.x > g_rtClient.right)
    {
        vPos.x = g_rtClient.right;
        _vDir.x *= -1.0f;
    }
    if (vPos.x < 0.0f)
    {
        vPos.x = 0.0f;
        _vDir.x *= -1.0f;
    }
    if (vPos.y > g_rtClient.bottom)
    {
        vPos.y = g_rtClient.bottom;
        _vDir.y *= -1.0f;
    }
    if (vPos.y < 0.0f)
    {
        vPos.y = 0.0f;
        _vDir.y *= -1.0f;
    }

    SetPosition(vPos);
	return true;
}