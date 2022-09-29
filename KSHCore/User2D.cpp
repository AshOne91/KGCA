#include "User2D.h"
#include "Input.h"

void User2D::UpdateVertexBuffer()
{
    _VertexList[0].p = { _vNDCPos.x, _vNDCPos.y, 0.0f };
    _VertexList[0].t = { _rtUV.x1, _rtUV.y1 };
    _VertexList[1].p = { _vNDCPos.x + _vDrawSize.x, _vNDCPos.y,  0.0f };
    _VertexList[1].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 };
    _VertexList[2].p = { _vNDCPos.x, _vNDCPos.y - _vDrawSize.y, 0.0f };
    _VertexList[2].t = { _rtUV.x1, _rtUV.y1 + _rtUV.h };
    _VertexList[3].p = { _vNDCPos.x + _vDrawSize.x, _vNDCPos.y - _vDrawSize.y, 0.0f };
    _VertexList[3].t = { _rtUV.x1 + _rtUV.w , _rtUV.y1 + _rtUV.h };

    Rotation();

    _pImmediateContext->UpdateSubresource(
        _pVertexBuffer, NULL, NULL, &_VertexList.at(0), 0, 0);
}

bool User2D::Frame()
{
    Vector2D vPos = _vPos;

    if (I_Input.GetKey('P'))
    {
        _fAngleDegree += 180.0f * g_fSecondPerFrame;
    }

    if (I_Input.GetKey('O'))
    {
        _fAngleDegree -= 180.0f * g_fSecondPerFrame;
    }

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