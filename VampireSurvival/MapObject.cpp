#include "MapObject.h"
#include "Spawner.h"
#include "Monster.h"
#include "MapObject.h"
#include "ObjectManager.h"
#include "Spawner.h"

bool MapObject::Init()
{
    Object2D::Init();
    _pSpawner = CreateObject<Spawner>();
    return true;
}

bool MapObject::Frame()
{
    SetPosition(_vPos, _vCameraPos);
    _transform.SetPostion(_vPos);
    _transform.SetRadious(1500.0f);
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

bool MapObject::CInit()
{
    MapObject::Init();
    return true;
}

bool MapObject::CFrame()
{
    MapObject::Frame();
    return true;
}

bool MapObject::CRender()
{
    MapObject::Render();
    return true;
}

bool MapObject::CRelease()
{
    MapObject::Release();
    ComponentObject::CRelease();
    return true;
}

bool MapObject::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
    return true;
}

void MapObject::EnableSpawner()
{
    _pSpawner->EnableSpawner();
}

void MapObject::DisableSpanwer()
{
    _pSpawner->DisableSpawner();
}
