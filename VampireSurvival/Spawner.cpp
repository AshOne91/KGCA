#include "Spawner.h"
#include "Monster.h"
#include "GameWorld.h"
#include "ObjectManager.h"

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
    _timerCounter.Start(2000);
    return true;
}

bool Spawner::CFrame()
{
    if (_timerCounter.IsFinished())
    {
        //_timerCounter.Start(2000);
        //I_GameWorld.AddMonster(SpawnMonster());
    }
    SetPosition(_vPos, I_GameWorld.GetCameraPos());
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

void Spawner::SetMonsterPrototype(Monster* pMonster)
{
    if (_pMonsterPrototype != nullptr)
    {
        delete _pMonsterPrototype;
        _pMonsterPrototype = nullptr;
    }
    _pMonsterPrototype = pMonster;
}

Monster* Spawner::SpawnMonster()
{
    return _pMonsterPrototype->Clone(this);
}
