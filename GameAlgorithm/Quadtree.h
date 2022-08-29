#pragma once
#include "SpacePartition.h"
class Quadtree :public SpacePartition
{
	const int MAX_QUADTREE_CHILD = 4;
public:
	virtual void Create(Vector2D pos, Vector2D size) override;
	virtual void DynamicObjectReset() override;

public:
	virtual void AddStaticObject(GameObject* pGameObject) override;
	virtual void AddDynamicObject(GameObject* pGameObject) override;

protected:
	virtual Node* FindNode(Node* pNode, GameObject* pObject) override;

private:
	Node* CreateNode(Node* pParent, Vector2D pos, Vector2D size);
	void Buildtree(Node* pNode);
	void DynamicReset(Node* pNode);
	bool IsNodeInObject(Node* pNode, GameObject* pGameObject);

public:
	Quadtree();
	virtual ~Quadtree();
};

