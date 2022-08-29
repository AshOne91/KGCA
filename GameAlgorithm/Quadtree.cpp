#include <queue>
#include "Quadtree.h"
#include "GameObject.h"

void Quadtree::Create(Vector2D pos, Vector2D size)
{
    _pRootNode = CreateNode(nullptr, pos, size);
    Buildtree(_pRootNode);
}

void Quadtree::DynamicObjectReset()
{
    DynamicReset(_pRootNode);
}

void Quadtree::AddStaticObject(GameObject* pGameObject)
{
    Node* pFindNode = FindNode(_pRootNode, pGameObject);
    if (pFindNode != nullptr)
    {
        pFindNode->_objectStaticList.push_back(pGameObject);
    }
}

void Quadtree::AddDynamicObject(GameObject* pGameObject)
{
    Node* pFindNode = FindNode(_pRootNode, pGameObject);
    if (pFindNode != nullptr)
    {
        pFindNode->_objectDynamicList.push_back(pGameObject);
    }
}

Node* Quadtree::FindNode(Node* pNode, GameObject* pObject)
{
    std::queue<Node*> queue;
    do
    {
        for (int iNode = 0; iNode < pNode->_pChild.size(); ++iNode)
        {
            if (pNode->_pChild[iNode] != nullptr)
            {
                bool bIn = IsNodeInObject(pNode->_pChild[iNode], pObject);
                if (bIn)
                {
                    queue.push(pNode->_pChild[iNode]);
                    break;
                }
            }
        }
        if (queue.empty()) break;
        pNode = queue.front();
        queue.pop();
    } while (pNode);
    return pNode;
}

Node* Quadtree::CreateNode(Node* pParent, Vector2D pos, Vector2D size)
{
    Node* pNode = new Node(pParent, pos, size);
    pNode->_pChild.resize(MAX_QUADTREE_CHILD);
    return pNode;
}

void Quadtree::Buildtree(Node* pNode)
{
    if (pNode->_depth >= 2) return;
    if (pNode == nullptr) return;

    Vector2D p, s;
    p.x = pNode->_box2D.x1;
    p.y = pNode->_box2D.y1;
    s.x = pNode->_box2D.w / 2.0f;
    s.y = pNode->_box2D.h / 2.0f;
    pNode->_pChild[0] = CreateNode(pNode, p, s);
    p.x = pNode->_box2D.x1 + s.x;
    p.y = pNode->_box2D.y1;
    pNode->_pChild[1] = CreateNode(pNode, p, s);
    p.x = pNode->_box2D.x1;
    p.y = pNode->_box2D.y1 + s.y;
    pNode->_pChild[2] = CreateNode(pNode, p, s);
    p.x = pNode->_box2D.x1 + s.x;
    p.y = pNode->_box2D.y1 + s.y;
    pNode->_pChild[3] = CreateNode(pNode, p, s);

    for (int iChild = 0; iChild < MAX_QUADTREE_CHILD; iChild++)
    {
        Buildtree(pNode->_pChild[iChild]);
    }
}

void Quadtree::DynamicReset(Node* pNode)
{
    if (pNode == nullptr)
    {
        return;
    }
    pNode->_objectDynamicList.clear();
    for (int iChild = 0; iChild < pNode->_pChild.size(); ++iChild)
    {
        DynamicReset(pNode->_pChild[iChild]);
    }
}

bool Quadtree::IsNodeInObject(Node* pNode, GameObject* pGameObject)
{
    auto type = Collision::CheckCollision(pNode->_box2D, pGameObject->_box2d);
    return type == CollisionType::IN;
}

Quadtree::Quadtree()
{
}

Quadtree::~Quadtree()
{
}
