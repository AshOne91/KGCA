#pragma once
#include <string>
#include <list>
#include "Node.h"

class GameObject;
class SpacePartition
{
protected:
	Node* _pRootNode;

public:
	virtual void Create(Vector2D pos, Vector2D size);
	virtual void Create(Vector3D pos, Vector3D size);
	virtual void DynamicObjectReset();

public:
	virtual void AddStaticObject(GameObject* pGameObject);
	virtual void AddDynamicObject(GameObject* pGameObject);
	virtual void RemoveDynamicObject(GameObject* pGameObject);

public:
	virtual void Pick(const Sphere& sphere, std::list<GameObject*>& pObject);

protected:
	virtual Node* FindNode(Node* pNode, GameObject* pObject);

public:
	SpacePartition();
	virtual ~SpacePartition();
};

