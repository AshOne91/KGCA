#include "SpacePartition.h"

void SpacePartition::Create(Vector2D pos, Vector2D size)
{
}

void SpacePartition::Create(Vector3D pos, Vector3D size)
{
}

void SpacePartition::DynamicObjectReset()
{
}

void SpacePartition::AddStaticObject(GameObject* pGameObject)
{
}

void SpacePartition::AddDynamicObject(GameObject* pGameObject)
{
}

void SpacePartition::RemoveDynamicObject(GameObject* pGameObject)
{
}

void SpacePartition::Pick(const Sphere& sphere, std::list<GameObject*>& pObject)
{
}

Node* SpacePartition::FindNode(Node* pNode, GameObject* pObject)
{
	return nullptr;
}

SpacePartition::SpacePartition()
{
}

SpacePartition::~SpacePartition()
{
}