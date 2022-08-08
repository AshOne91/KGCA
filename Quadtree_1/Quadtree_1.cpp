#include "TCollision.h"
std::queue<TNode*> g_Queue;
class TObject
{
public:
    TRect _rt;
    void SetPosition(float x, float y, float w, float h)
    {
        _rt.Set(x, y, w, h);
    }
    TObject()
    {
        _rt.Set(20 + (rand() % 80), 20 + (rand() % 80), 10, 10);
    }
};
class TNode
{
public:
    TRect _rt;
    int _depth;
    std::vector<TObject*> _objectList;
    TNode* _pChild[4];
    TNode* _pParent;
public:
    TNode(TNode* pParent, float x, float y, float w, float h)
    {
        _rt._x = x;
        _rt._y = y;
        _rt._w = w;
        _rt._h = h;
        _depth = 0;
        if (pParent != NULL)
        {
            _pParent = pParent;
            _depth = pParent->_depth + 1;
        }
    }
    ~TNode()
    {
        delete _pChild[0];
        delete _pChild[1];
        delete _pChild[2];
        delete _pChild[3];
    }
};
class TQuadtree
{
public:
    TNode* _pRootNode;
public:
    std::vector<TObject*> Collision(TObject* pObj);
    void Create(float width, float height);
    TNode* CreateNode(TNode* pParent,
        float fPosX, float fPosY, float fWidth, float fHeight);
    void Buildtree(TNode* pNode);
    void AddObject(TObject* pObj);
    TNode* FindNode(TNode* pNode, TObject* pObj);
    void GetCollisionObject(TNode* pNode, TObject* pObj, std::vector<TObject*>&);
    ~TQuadtree()
    {
        delete _pRootNode;
    }
};

std::vector<TObject*> TQuadtree::Collision(TObject* pObj)
{
    std::vector<TObject*> list;
    GetCollisionObject(_pRootNode, pObj, list);
    return list;
}
void TQuadtree::GetCollisionObject(TNode* pNode, TObject* pSrcObject, std::vector<TObject*>& list)
{
    if (pNode == nullptr) return;
    for (int iObj = 0; iObj < pNode->_objectList.size(); ++iObj)
    {
        //��� ��������
        if (TCollision::RectToRect(pNode->_objectList[iObj]->_rt, pSrcObject->_rt))
        {
            list.push_back(_pRootNode->_objectList[iObj]);
        }
    }
    if (pNode->_pChild[0] != nullptr)
    {
        for (int iChild = 0; iChild < 4; iChild++)
        {
            //��� ��������(�������� �־)
            if (TCollision::RectToRect(pNode->_pChild[iChild]->_rt, pSrcObject->_rt))
            {
                GetCollisionObject(pNode->_pChild[iChild], pSrcObject, list);
            }
        }
    }
}
// 1�� : ������ �����ϴ� ��忡 �߰�����.
// 2�� : ���ĸ� �־ ��忡 �߰�����.
void TQuadtree::AddObject(TObject* pObj)
{
    // ��Ʈ�� ���ԵǴ�?
    // 1�ڽ� ? -->
    // 2�ڽ� ? -->

    //��Ʈ�ȿ� ���ԵǾ��� --> �ƴϿ� ����....
    //������

    TNode* pFindNode = FindNode(_pRootNode, pObj);
    if (pFindNode != nullptr)
    {
        pFindNode->_objectList.push_back(pObj);
    }
}

TNode* TQuadtree::FindNode(TNode* pNode, TObject* pObj)
{
    do
    {
        for (int iNode = 0; iNode < 4; iNode++)
        {
            if (pNode->_pChild[iNode] != nullptr)
            {
                bool bIn = TCollision::RectToInRect(pNode->_pChild[iNode]->_rt, pObj->_rt);
                if (bIn > 0)
                {
                    g_Queue.push(pNode->_pChild[iNode]);
                    break;
                }
            }
            if (g_Queue.empty()) break;
            pNode = g_Queue.front();
            g_Queue.pop();
        }
    } while (pNode);
    return pNode;
}
void TQuadtree::Buildtree(TNode* pNode)
{
    if (pNode->_depth >= 2) return;
    if (pNode == nullptr) return;

    float x, y, w, h;
    x = pNode->_rt._x;
    y = pNode->_rt._y;
    w = pNode->_rt._w / 2.0f;
    h = pNode->_rt._h / 2.0f;
    pNode->_pChild[0] = CreateNode(pNode, x, y, w, h);
    x = pNode->_rt._x + w;
    y = pNode->_rt._y;
    pNode->_pChild[1] = CreateNode(pNode, x, y, w, h);
    x = pNode->_rt._x;
    y = pNode->_rt._y + h;
    pNode->_pChild[2] = CreateNode(pNode, x, y, w, h);
    x = pNode->_rt._x + w;
    y = pNode->_rt._y + h;
    pNode->_pChild[3] = CreateNode(pNode, x, y, w, h);

    for (int iChild = 0; iChild < 4; iChild++)
    {
        Buildtree(pNode->_pChild[iChild]);
    }
}
void TQuadtree::Create(float width, float height)
{
    _pRootNode = CreateNode(nullptr, 0, 0, width, height);
    Buildtree(_pRootNode);
}
TNode* TQuadtree::CreateNode(TNode* pParent,
    float x, float y, float w, float h)
{
    TNode* pNode = new TNode(pParent, x, y, w, h);
    return pNode;
}
int main()
{
    TObject player;
    player.SetPosition(40, 60, 10, 10);
    TQuadtree quadtree;
    quadtree.Create(100.0f, 100.0f);
    for (int i = 0; i < 10; ++i)
    {
        TObject* pObj = new TObject;
        quadtree.AddObject(pObj);
    }
    //TNode* pNodePlayer = quadtree.FindNode(quadtree._pRootNode, &player);
    std::vector<TObject*> list = quadtree.Collision(&player);
    if (!list.empty())
    {
        for (int iObj = 0; iObj < list.size(); iObj++)
        {
            std::cout << list[iObj]->_rt._x
                << list[iObj]->_rt._y << std::endl;
        }
    }

    //while (true)
    //{
        //quadtree.MoveObject();
    //}
    //ȭ����ǥ��
    //0,0 -> x   50,0       100(x), 0(y)
    //|     0           1
    //y 0,50    50,50       100,50
    //      2           3
    //0, 100    50,100      100, 100
    std::cout << "Hello World!\n";
}
