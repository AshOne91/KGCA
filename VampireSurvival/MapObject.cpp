#include "MapObject.h"
#include "Spawner.h"
#include "Monster.h"

void MapObject::SetMonsterPrototype(Monster* pMonster)
{
    _pSpawner->SetMonsterPrototype(pMonster);
}

bool MapObject::Init()
{
    Object2D::Init();
    _pSpawner = new Spawner();
    _pSpawner->Create(_pd3dDevice, _pImmediateContext, L"../../data/shader/DefaultShape.txt", L"");
    _pSpawner->Init();
    return true;
}

bool MapObject::Frame()
{
    SetPosition(_vPos, _vCameraPos);
    _pSpawner->SetPosition(_vPos, _vCameraPos);
    _pSpawner->Frame();
    return true;
}
bool MapObject::Render()
{
    Object2D::Render();
    _pSpawner->Render();
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
