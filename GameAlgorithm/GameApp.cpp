#include <chrono>
#include "Player.h"
#include "GameApp.h"
#include "Octree.h"
#include "GameObject.h"
#include "Monster.h"

GameApp::GameApp() : 
	_frame(10)
	, _frameDelay(1000 / _frame)
	, _running(false)
{

}

GameApp::~GameApp()
{

}

void GameApp::Create(Config config)
{
	_console.Initial();
	_frame = config._frame;
	_frameDelay = 1000 / _frame;
	_frameSkip.SetFramePerSec((float)_frame);
	_CreateOcTree();
	_pPossessObj = new Player(this, 25.0f, 25.0f, 17.0f, 1.0f);
	_objectList.insert({ _pPossessObj->GetObjectIdx(), _pPossessObj });
	_running = true;
}

bool GameApp::Run()
{
	std::chrono::system_clock::time_point lastTick = std::chrono::system_clock::now();
	float totalDeltaTime = 0.0f;
	while (_running)
	{
		std::chrono::system_clock::time_point curTick = std::chrono::system_clock::now();
		std::chrono::milliseconds deltaTick = std::chrono::duration_cast<std::chrono::milliseconds>(curTick - lastTick);
		lastTick = curTick;
		float dt = deltaTick.count() * 0.001f;
		totalDeltaTime += dt;
		_Input();
		if (_frameSkip.Update(dt))
		{
			_Update(totalDeltaTime);
			totalDeltaTime = 0.0f;
		}
		else
		{
			_Render();
		}
	}
}

void GameApp::_Input()
{
	Command* command = _InputHandler.handleInput();
	if (command)
	{
		command->execute(_pPossessObj);
	}
}

void GameApp::_Update(float dt)
{
	_SpawnMonster(dt);

	for (auto obj : _objectList)
	{
		if (obj.second->GetActive() == GameObject::enActive::Active)
		{
			obj.second->Update(dt);
		}
	}
	_PendingRemoveObj();
}

void GameApp::_Render()
{
	for (auto obj : _objectList)
	{
		switch (obj.second->GetType())
		{
		case GameObject::enObjectType::Player:
		{
			_console.Sprite_Draw(obj.second->GetPosition().x, obj.second->GetPosition().y, 'P');
			break;
		}
		case GameObject::enObjectType::Monster:
		{
			_console.Sprite_Draw(obj.second->GetPosition().x, obj.second->GetPosition().y, 'M');
			break;
		}
		case GameObject::enObjectType::Missile:
		{
			_console.Sprite_Draw(obj.second->GetPosition().x, obj.second->GetPosition().y, '*');
			break;
		}
		default:
			break;
		}
	}
	_console.BufferFlip();
	_console.BufferDraw();
	_console.BufferClear();
}

void GameApp::_CreateOcTree()
{
	_pPartiton = new Octree();
	_pPartiton->Create(Vector3D(0, 0, 0), Vector3D(50, 50, 50));
}

void GameApp::_PendingRemoveObj()
{
	for (auto idx : _pendingRemoveObjectIdx)
	{
		delete _objectList[idx];
		_objectList.erase(idx);
	}

	_pendingRemoveObjectIdx.clear();
}

void GameApp::_SpawnMonster(float dt)
{
	_spawnDelay += dt;
	if (_spawnDelay > 2.0f)
	{
		_spawnDelay = 0.0f;
		float x = rand() % dfSCREEN_WIDTH;
		float y = 0;
		GameObject* monster = new Monster(this, (unsigned __int64)GameObject::enFaction::Monster, x, y, 17.0f, 1.0f);
		AddObject(monster);
	}
}

std::list<GameObject*> GameApp::GetObjects(Vector3D position, float radius, unsigned __int64 faction)
{

}

GameObject* GameApp::GetObject(unsigned __int64 objectIdx)
{
	auto iter = _objectList.find(objectIdx);
	if (iter != _objectList.end())
	{
		return iter->second;
	}
	return nullptr;
}

void GameApp::OctreeUpdateNode(GameObject* obj)
{
}

void GameApp::InsertObjectOctree(GameObject* obj)
{
}

bool GameApp::RemoveObjectOctree(GameObject* obj)
{
	return false;
}

bool GameApp::AddObject(GameObject* obj)
{
	return false;
}

bool GameApp::Destroy(GameObject* obj)
{
	return false;
}
