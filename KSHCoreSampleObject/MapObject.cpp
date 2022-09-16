#include "MapObject.h"

bool MapObject::FrameScroll()
{
    static float fStep = 0.0f;
    /* UINT iMapWidth = m_pTexture->m_Desc.Width;
     if (I_Input.GetKey('W') > 0)
     {
         m_vUserPos.y += g_fSecondPerFrame * 10.0f;
         if (iMapWidth > m_vUserPos.x)
         {
             fStep = m_vUserPos.y / iMapWidth;
         }

     }*/
    if (fStep + 0.1f <= 1.0f)
    {
        fStep += g_fSecondPerFrame * 0.01f;
    }

    _VertexList[0].p = { -1.0f, 1.0f, 0.0f };
    _VertexList[1].p = { +1.0f, 1.0f,  0.0f };
    _VertexList[2].p = { -1.0f, -1.0f, 0.0f };
    _VertexList[3].p = { 1.0f, -1.0f, 0.0f };

    _VertexList[0].t = { 0.0f, 0.0f + fStep };
    _VertexList[1].t = { 1.0f, 0.0f + fStep };
    _VertexList[2].t = { 0.0f, 0.1f + fStep };
    _VertexList[3].t = { 1.0f, 0.1f + fStep };

    // gpu update
    _pImmediateContext->UpdateSubresource(
        _pVertexBuffer, 0, NULL,
        &_VertexList.at(0), 0, 0);
    return true;
}

bool MapObject::Frame()
{
    SetPosition(_vPos, _vCameraPos);
    return true;
}

void  MapObject::UpdateVertexBuffer()
{
    _VertexList[0].p = { _vDrawPos.x, _vDrawPos.y, 0.0f };
    _VertexList[1].p = { _vDrawPos.x + _vDrawSize.x, _vDrawPos.y,  0.0f };
    _VertexList[2].p = { _vDrawPos.x, _vDrawPos.y - _vDrawSize.y, 0.0f };
    _VertexList[3].p = { _vDrawPos.x + _vDrawSize.x, _vDrawPos.y - _vDrawSize.y, 0.0f };
    _pImmediateContext->UpdateSubresource(
        _pVertexBuffer, NULL, NULL, &_VertexList.at(0), 0, 0);
}