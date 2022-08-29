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
    if (pNode->_depth >= 3) return;
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
	return type == CollisionType::IN;
}

Octree::Octree()
{
}

Octree::~Octree()
{
}
