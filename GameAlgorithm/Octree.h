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
	virtual void RemoveDynamicObject(GameObject* pGameObject) override;

public:
	virtual void Pick(const Sphere& sphere, std::list<GameObject*>& pObject);

protected:
	virtual Node* FindNode(Node* pNode, GameObject* pObject) override;

private:
	Node* CreateNode(Node* pParent, Vector3D pos, Vector3D size);
	void Buildtree(Node* pNode);
	void DynamicReset(Node* pNode);
	bool IsNodeInObject(Node* pNode, GameObject* pGameObject);
	bool IsCollision(GameObject* pDest, GameObject* pSrc);
	bool IsCollision(Node* pNode, GameObject* pSrc);
	bool IsCollision(const Sphere& sphere, GameObject* pSrc);
	bool IsCollision(const Sphere& sphere, Node* pNode);
	void    GetCollisitionObject(Node* pNode, GameObject* pSrcObject,
		std::vector<GameObject*>& list);
	void Pick(Node* pNode, const Sphere& sphere, std::list<GameObject*>& pObject);

public:
	Octree();
	virtual ~Octree();
};

