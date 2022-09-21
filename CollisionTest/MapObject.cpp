#include "MapObject.h"
#include "Input.h"

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