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
	delete _pPartiton;
	for (auto kv : _objectList)
	{
		delete kv.second;
	}
}

void GameApp::Create(Config config)
{
	_console.Initial();
	_frame = config._frame;
	_frameDelay = 1000 / _frame;
	_frameSkip.SetFramePerSec((float)_frame);
	_CreateOcTree();
	_pPossessObj = new Player(this, Vector3D(25.0f,25.0f,25.0f), Vector3D(1.0f, 1.0f, 1.0f));
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
		_Input(dt);
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
	return true;
}

void GameApp::_Input(float dt)
{
	Command* command = _InputHandler.handleInput();
	if (command)
	{
		command->execute(_pPossessObj, dt);
	}
}

void GameApp::_Update(float dt)
{
	_PendingRemoveObj();
	OctreeUpdate();
	_SpawnMonster(dt);
	for (auto obj : _objectList)
	{
		if (obj.second->GetActive() == enActive::Active)
		{
			obj.second->Update(dt);
		}
	}
}

void GameApp::_Render()
{
	for (auto obj : _objectList)
	{
		switch (obj.second->GetType())
		{
		case enObjectType::Player:
		{
			_console.Sprite_Draw(obj.second->GetPosition().x, obj.second->GetPosition().y, 'P');
			break;
		}
		case enObjectType::Monster:
		{
			_console.Sprite_Draw(obj.second->GetPosition().x, obj.second->GetPosition().y, 'M');
			break;
		}
		case enObjectType::Missile:
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
		GameObject* monster = new Monster(this, (unsigned __int64)enFaction::Monster, Vector3D(x, y, 25.0f), Vector3D(1.0f, 1.0f, 1.0f));
		AddObject(monster);
	}
}

std::list<GameObject*> GameApp::GetObjects(Vector3D position, float radius, unsigned __int64 faction)
{
	std::list<GameObject*> pickedList;
	Sphere sphere;
	sphere.center = position;
	sphere.radius = radius;
	_pPartiton->Pick(sphere, pickedList);

	std::list<GameObject*> resultObjs;
	for (auto obj : pickedList)
	{
		GameObject* castObj = dynamic_cast<GameObject*>(obj);
		if (castObj != nullptr)
		{
			if (castObj->CheckFaction((unsigned __int64)faction))
			{
				resultObjs.push_back(castObj);
			}
		}
	}

	return resultObjs;
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

void GameApp::OctreeUpdate()
{
	_pPartiton->DynamicObjectReset();
	for (auto kv : _objectList)
	{
		if (kv.second->GetActive() == enActive::Active)
		{
			_pPartiton->AddDynamicObject(kv.second);
		}
	}
}

void GameApp::InsertObjectOctree(GameObject* obj)
{
	_pPartiton->AddDynamicObject(obj);
}

bool GameApp::RemoveObjectOctree(GameObject* obj)
{
	_pPartiton->RemoveDynamicObject(obj);
	return false;
}

bool GameApp::AddObject(GameObject* obj)
{
	_objectList.insert({ obj->GetObjectIdx(), obj });
	return false;
}

bool GameApp::Destroy(GameObject* obj)
{
	obj->SetActive(enActive::Destroy);
	_pendingRemoveObjectIdx.push_back(obj->GetObjectIdx());
	RemoveObjectOctree(obj);
	return false;
}

bool CheckRangeOut(float x, float y)
{
	if (y < 0)
		return true;
	if (y > dfSCREEN_HEIGHT)
		return true;
	if (x < 0)
		return true;
	if (x > dfSCREEN_WIDTH)
		return true;

	return false;
}
