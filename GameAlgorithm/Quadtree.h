#pragma once
#include "SpacePartition.h"
class Quadtree :public SpacePartition
{
public:
	virtual void Create(Vector2D pos, Vector2D size) override;
	virtual void DynamicObjectReset() override;

public:
	virtual void AddStaticObject(GameObject* pGameObject) override;
	virtual void AddDynamicObject(GameObject* pGameObject) override;

protected:
	virtual Node* FindNode(Node* pNode, GameObject* pObject) override;



public:
	Quadtree();
	virtual ~Quadtree();
};

