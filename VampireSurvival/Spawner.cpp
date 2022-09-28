#include "Spawner.h"
#include "Monster.h"
#include "GameWorld.h"

bool Spawner::Init()
{
    _timerCounter.Start(2000);
    return false;
}

bool Spawner::Frame()
{
    if (_timerCounter.IsFinished())
    {
        _timerCounter.Start(2000);
        auto pMonster = new Monster(100, 100);
        I_GameWorld.AddMonster(SpawnMonster());
    }
    SetPosition(_vPos, I_GameWorld.GetCameraPos());
    return false;
}

bool Spawner::Render()
{
    return false;
}

bool Spawner::Release()
{
    if (_pMonsterPrototype) _pMonsterPrototype->Release();
    _pMonsterPrototype = nullptr;
    return false;
}

void Spawner::SetMonsterPrototype(Monster* pMonster)
{
    if (_pMonsterPrototype != nullptr)
    {
        _pMonsterPrototype->Release();
        delete _pMonsterPrototype;
    }
    _pMonsterPrototype = pMonster;
}

Monster* Spawner::SpawnMonster()
{
    return _pMonsterPrototype->Clone(this);
}
