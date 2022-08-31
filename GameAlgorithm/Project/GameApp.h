#pragma once
#include <list>
#include <unordered_map>
#include "Console.h"
#include "Config.h"
#include "Vector.h"
#include "FrameSkip.h"
#include "InputHandler.h"

class GameObject;
class SpacePartition;
class GameApp
{
private:
	int _frame;
	int _frameDelay;
	bool _running = false;
	FrameSkip _frameSkip;
	SpacePartition* _pPartiton;
	std::unordered_map<unsigned __int64, GameObject*> _objectList;
	std::list<unsigned __int64> _pendingRemoveObjectIdx;
	GameObject* _pPossessObj;
	InputHandler _InputHandler;
	Console _console;
	float _spawnDelay = 0.0f;

public:
	GameApp();
	virtual ~GameApp();

public:
	void Create(Config config);
	bool Run();

private:
	void _Input(float dt);
	void _Update(float dt);
	void _Render();
	void _CreateOcTree();
	void _PendingRemoveObj();
	void _SpawnMonster(float dt);

public:
	std::list<GameObject*> GetObjects(Vector3D position, float radius, unsigned __int64 faction);
	GameObject* GetObject(unsigned __int64 objectIdx);
	void OctreeUpdate();
	void InsertObjectOctree(GameObject* obj);
	bool RemoveObjectOctree(GameObject* obj);

	bool AddObject(GameObject* obj);
	bool Destroy(GameObject* obj);
};

bool CheckRangeOut(float x, float y);