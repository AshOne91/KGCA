#pragma once
#include "SpacePartition.h"
class Octree : public SpacePartition
{
public:
	virtual void Create(Vector3D pos, Vector3D size);
	virtual void DynamicObjectReset();

public:
	virtual void AddStaticObject(GameObject* pGameObject);
	virtual void AddDynamicObject(GameObject* pGameObject);

protected:
	virtual Node* FindNode(Node* pNode, GameObject* pObject);

public:
	Octree();
	virtual ~Octree();
};

