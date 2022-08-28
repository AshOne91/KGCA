#pragma once
#include <string>
#include "Node.h"

enum class TYPE : int
{
	QUADTREE,
	OCTREE,
	BSP
};

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

protected:
	virtual Node* FindNode(Node* pNode, GameObject* pObject);

public:
	SpacePartition();
	virtual ~SpacePartition();
};

