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

bool Spawner::Release()
{
    return true;
}

bool Spawner::CInit()
{
    this->Create(I_GameWorld.GetDevice(), I_GameWorld.GetDeviceImmediateContext(), L"../../data/shader/DefaultShape.txt", L"");
    return true;
}

bool Spawner::CFrame()
{
    SetPosition(_vPos, I_GameWorld.GetCameraPos());
   // static int count = 0;
    if (_timerCounter.IsFinished())
    {
       // count++;
       // if (count > 1)
       // {
            //return true;
       // }
        _timerCounter.Start(200);
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
    //if (_pMonsterPrototype) _pMonsterPrototype->Release();
    //_pMonsterPrototype = nullptr;
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
