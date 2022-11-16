#include "Spawner.h"
#include "Monster.h"
#include "GameWorld.h"
#include "ObjectManager.h"
#include "Utils.h"

bool Spawner::Init()
{
    return true;
}

bool Spawner::Frame()
{
    return true;
}

bool Spawner::Render()
{
    return true;
}

bool Spawner::CInit()
{
    this->Create(I_GameWorld.GetDevice(), I_GameWorld.GetDeviceImmediateContext(), L"DefaultShape.txt", L"");
    return true;
}

bool Spawner::CFrame()
{
    SetPosition(_vPos, I_GameWorld.GetCameraPos());
    if (_timerCounter.IsFinished())
    {
        _timerCounter.Start(100);
        auto pMonster = CreateObject<Monster>();
        float RangeX = KSHCore::UTIL::RandInRange(-250, 250);
        float RangeY = KSHCore::UTIL::RandInRange(-250, 250);
        Vector2D SpanwPos = Vector2D(_vPos.x + RangeX, _vPos.y + RangeY);
        pMonster->SetPosition(SpanwPos, I_GameWorld.GetCameraPos());
    }
    return true;
}

bool Spawner::CRender()
{
    return true;
}

bool Spawner::CRelease()
{
    Spawner::Release();
    ComponentObject::CRelease();
    return true;
}

bool Spawner::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
    return true;
}

void Spawner::EnableSpawner()
{
    _timerCounter.SetActive(true);
}

void Spawner::DisableSpawner()
{
    _timerCounter.SetActive(false);
}
