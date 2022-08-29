#include <queue>
#include "Octree.h"
#include "GameObject.h"

void Octree::Create(Vector3D pos, Vector3D size)
{
	_pRootNode = CreateNode(nullptr, pos, size);
	Buildtree(_pRootNode);
}

void Octree::DynamicObjectReset()
{
	DynamicReset(_pRootNode);
}

void Octree::AddStaticObject(GameObject* pGameObject)
{
	Node* pFindNode = FindNode(_pRootNode, pGameObject);
	if (pFindNode != nullptr)
	{
		pFindNode->_objectStaticList.push_back(pGameObject);
	}
}

void Octree::AddDynamicObject(GameObject* pGameObject)
{
	Node* pFindNode = FindNode(_pRootNode, pGameObject);
	if (pFindNode != nullptr)
	{
		pFindNode->_objectDynamicList.push_back(pGameObject);
	}
}

void Octree::RemoveDynamicObject(GameObject* pGameObject)
{
    if (pGameObject->_pNode == nullptr)
    {
        return;
    }

    auto it = pGameObject->_pNode->_objectDynamicList.begin();
    while (it != pGameObject->_pNode->_objectDynamicList.end())
    {
        if ((*it) == pGameObject)
        {
            pGameObject->_pNode->_objectDynamicList.erase(it);
            break;
        }
    }
}

void Octree::Pick(const Sphere& sphere, std::list<GameObject*>& pObject)
{
    Pick(_pRootNode, sphere, pObject);
}

Node* Octree::FindNode(Node* pNode, GameObject* pObject)
{
    std::queue<Node*> g_Queue;
    do {
        for (int iNode = 0; iNode < pNode->_pChild.size(); iNode++)
        {
            if (pNode->_pChild[iNode] != nullptr)
            {
                bool bIn = IsNodeInObject(pNode->_pChild[iNode], pObject);
                if (bIn)
                {
                    g_Queue.push(pNode->_pChild[iNode]);
                    break;
                }
            }
        }
        if (g_Queue.empty()) break;
        pNode = g_Queue.front();
        g_Queue.pop();
    } while (pNode);
    return pNode;
}

Node* Octree::CreateNode(Node* pParent, Vector3D pos, Vector3D size)
{
    Node* pNode = new Node(pParent, pos, size);
    pNode->_pChild.resize(MAX_OCTREE_CHILD);
    return pNode;
}

void Octree::Buildtree(Node* pNode)
{
    if (pNode->_depth >= 2) return;
    if (pNode == nullptr) return;

    Vector3D pos;
    Vector3D size;
    pos = pNode->_box3D.min;
    size = pNode->_box3D.size / 2.0f;
    pNode->_pChild[0] = CreateNode(pNode, pos, size);
    pos.x = pNode->_box3D.min.x + size.x;
    pNode->_pChild[1] = CreateNode(pNode, pos, size);
    pos.x = pNode->_box3D.min.x;
    pos.y = pNode->_box3D.min.y + size.y;
    pNode->_pChild[2] = CreateNode(pNode, pos, size);
    pos.x = pNode->_box3D.min.x + size.x;
    pos.y = pNode->_box3D.min.y + size.y;
    pNode->_pChild[3] = CreateNode(pNode, pos, size);

    pos.x = pNode->_box3D.min.x;
    pos.y = pNode->_box3D.min.y;
    pos.z = pNode->_box3D.min.z + size.z;
    pNode->_pChild[4] = CreateNode(pNode, pos, size);
    pos.x = pNode->_box3D.min.x + size.x;
    pos.y = pNode->_box3D.min.y;
    pNode->_pChild[5] = CreateNode(pNode, pos, size);
    pos.x = pNode->_box3D.min.x;
    pos.y = pNode->_box3D.min.y + size.y;
    pNode->_pChild[6] = CreateNode(pNode, pos, size);
    pos.x = pNode->_box3D.min.x + size.x;
    pos.y = pNode->_box3D.min.y + size.y;
    pNode->_pChild[7] = CreateNode(pNode, pos, size);

    for (int iChild = 0; iChild < pNode->_pChild.size(); iChild++)
    {
        Buildtree(pNode->_pChild[iChild]);
    }
}

void Octree::DynamicReset(Node* pNode)
{
    if (pNode == nullptr) return;
    pNode->_objectDynamicList.clear();
    for (int iChild = 0; iChild < pNode->_pChild.size(); iChild++)
    {
        DynamicReset(pNode->_pChild[iChild]);
    }
}

bool Octree::IsNodeInObject(Node* pNode, GameObject* pGameObject)
{
    auto type = Collision::CheckCollision(pNode->_box3D, pGameObject->_box3d);
	return type == CollisionType::COLLISON_IN;
}

bool Octree::IsCollision(GameObject* pDest, GameObject* pSrc)
{
    auto type = Collision::CheckCollision(pDest->_sphere, pSrc->_sphere);
    if (type != CollisionType::COLLISON_OUT)
    {
        type = Collision::CheckCollision(pDest->_box3d, pDest->_box3d);
        if (type != CollisionType::COLLISON_OUT)
        {
            return true;
        }
    }
    return false;
}

bool Octree::IsCollision(Node* pNode, GameObject* pSrc)
{
    auto type = Collision::CheckCollision(pNode->_box3D, pNode->_box3D);
    if (type != CollisionType::COLLISON_OUT)
    {
        return true;
    }
    return false;
}

bool Octree::IsCollision(const Sphere& sphere, GameObject* pSrc)
{
    auto type = Collision::CheckCollision(sphere, pSrc->_sphere);
    if (type != CollisionType::COLLISON_OUT)
    {
        return true;
    }
    return false;
}

bool Octree::IsCollision(const Sphere& sphere, Node* pNode)
{
    auto type = Collision::CheckCollision(sphere, pNode->_sphere);
    if (type != CollisionType::COLLISON_OUT)
    {
        return true;
    }
    return false;
}

void Octree::GetCollisitionObject(Node* pNode, GameObject* pSrcObject, std::vector<GameObject*>& list)
{
    if (pNode == nullptr) return;
    for (int iObj = 0; iObj < pNode->_objectStaticList.size(); iObj++)
    {
        if (IsCollision(pNode->_objectStaticList[iObj], pSrcObject))
        {
            list.push_back(pNode->_objectStaticList[iObj]);
        }
    }
    for (int iObj = 0; iObj < pNode->_objectDynamicList.size(); iObj++)
    {
        if (IsCollision(pNode->_objectDynamicList[iObj], pSrcObject))
        {
            list.push_back(pNode->_objectDynamicList[iObj]);
        }
    }
    if (pNode->_pChild[0] != nullptr)
    {
        for (int iChild = 0; iChild < pNode->_pChild.size(); iChild++)
        {
            if (IsCollision(pNode->_pChild[iChild], pSrcObject))
            {
                GetCollisitionObject(pNode->_pChild[iChild], pSrcObject, list);
            }
        }
    }
}

void Octree::Pick(Node* pNode, const Sphere& sphere, std::list<GameObject*>& list)
{
    if (pNode == nullptr)
    {
        return;
    }
    for (int iObj = 0; iObj < pNode->_objectStaticList.size(); iObj++)
    {
        if (IsCollision(sphere, pNode->_objectStaticList[iObj]))
        {
            list.push_back(pNode->_objectStaticList[iObj]);
        }
    }
    for (int iObj = 0; iObj < pNode->_objectDynamicList.size(); iObj++)
    {
        if (IsCollision(sphere, pNode->_objectDynamicList[iObj]))
        {
            list.push_back(pNode->_objectDynamicList[iObj]);
        }
    }
    if (pNode->_pChild[0] != nullptr)
    {
        for (int iChild = 0; iChild < pNode->_pChild.size(); iChild++)
        {
            if (IsCollision(sphere, pNode->_pChild[iChild]))
            {
                Pick(pNode->_pChild[iChild], sphere, list);
            }
        }
    }
}

Octree::Octree()
{
}

Octree::~Octree()
{
}
