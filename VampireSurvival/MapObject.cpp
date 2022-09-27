#include "MapObject.h"

bool MapObject::Init()
{
    Object2D::Init();
    _pSpawner = new Spawner();
    return true;
}

bool MapObject::Frame()
{
    SetPosition(_vPos, _vCameraPos);
    _pSpawner->SetPosition(_vPos, _vCameraPos);
    return true;
}
bool MapObject::Render()
{
    Object2D::Render();
    return true;
}
bool MapObject::Release()
{
    Object2D::Release();
    if (_pSpawner) _pSpawner->Release();
    return true;
}
void MapObject::UpdateVertexBuffer()
{
    _VertexList[0].p = { _vNDCPos.x, _vNDCPos.y, 0.0f };
    _VertexList[1].p = { _vNDCPos.x + _vDrawSize.x, _vNDCPos.y,  0.0f };
    _VertexList[2].p = { _vNDCPos.x, _vNDCPos.y - _vDrawSize.y, 0.0f };
    _VertexList[3].p = { _vNDCPos.x + _vDrawSize.x, _vNDCPos.y - _vDrawSize.y, 0.0f };
    _pImmediateContext->UpdateSubresource(
        _pVertexBuffer, NULL, NULL, &_VertexList.at(0), 0, 0);
}
