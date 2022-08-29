#pragma once
#include "SpacePartition.h"
class Octree : public SpacePartition
{
	const int MAX_OCTREE_CHILD = 8;
public:
	virtual void Create(Vector3D pos, Vector3D size) override;
	virtual void DynamicObjectReset() override;

public:
	virtual void AddStaticObject(GameObject* pGameObject) override;
	virtual void AddDynamicObject(GameObject* pGameObject) override;

protected:
	virtual Node* FindNode(Node* pNode, GameObject* pObject) override;

private:
	Node* CreateNode(Node* pParent, Vector3D pos, Vector3D size);
	void Buildtree(Node* pNode);
	void DynamicReset(Node* pNode);
	bool IsNodeInObject(Node* pNode, GameObject* pGameObject);

public:
	Octree();
	virtual ~Octree();
};

