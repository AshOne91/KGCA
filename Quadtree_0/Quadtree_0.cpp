#include <iostream>
#include <vector>
#include <queue>
std::queue<TNode*> g_Queue;
class TObject
{
public:
    float _x;
    float _y;
    float _w;
    float _h;
    TObject()
    {
        _x = rand() % 100;
        _y = rand() % 100;
        _w = 2.0f + (rand() % 10);
        _h = 2.0f + (rand() % 10);
    }
};
class TNode
{
public:
    float _x;
    float _y;
    float _w;
    float _h;
    int _depth;
    std::vector<TObject*> _objectList;
    TNode* _pChild[4];
    TNode* _pParent;
public:
    TNode(TNode* pParent, float x, float y, float w, float h)
    {
        _x = x;
        _y = y;
        _w = w;
        _h = h;
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
    void Create(float width, float height);
    TNode* CreateNode(TNode* pParent,
        float fPosX, float fPosY, float fWidth, float fHeight);
    void Buildtree(TNode* pNode);
    void AddObject(TObject* pObj);
    TNode* FindNode(TNode* pNode, TObject* pObj);
    bool RectToRect(TNode* pNode, TObject* pObj);
    ~TQuadtree()
    {
        delete _pRootNode;
    }
};

bool TQuadtree::RectToRect(TNode* pNode, TObject* pObj)
{
    if (pNode->_x <= pObj->_x)
    {
        if ((pNode->_x + pNode->_w) >= pObj->_x + pObj->_w)
        {
            if (pNode->_y <= pObj->_y)
            {
                if ((pNode->_y + pNode->_h) >= pObj->_y + pObj->_h)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
// 1번 : 완전히 포함하는 노드에 추가하자.
// 2번 : 걸쳐만 있어도 노드에 추가하자.
void TQuadtree::AddObject(TObject* pObj)
{
    // 루트에 포함되니?
    // 1자식 ? -->
    // 2자식 ? -->

    //루트안에 포함되었니 --> 아니여 리턴....
    //오케이

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
                bool bIn = RectToRect(pNode->_pChild[iNode], pObj);
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
    x = pNode->_x;
    y = pNode->_y;
    w = pNode->_w / 2.0f;
    h = pNode->_h / 2.0f;
    pNode->_pChild[0] = CreateNode(pNode, x, y, w, h);
    x = pNode->_x + w;
    y = pNode->_y;
    pNode->_pChild[1] = CreateNode(pNode, x, y, w, h);
    x = pNode->_x;
    y = pNode->_y + h;
    pNode->_pChild[2] = CreateNode(pNode, x, y, w, h);
    x = pNode->_x + w;
    y = pNode->_y + h;
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
    TQuadtree quadtree;
    quadtree.Create(100.0f, 100.0f);
    for (int i = 0; i < 10; ++i)
    {
        TObject* pObj = new TObject;
        quadtree.AddObject(pObj);
    }
    while (true)
    {
        //quadtree.MoveObject();
    }
    //화면좌표계
    //0,0 -> x   50,0       100(x), 0(y)
    //|     0           1
    //y 0,50    50,50       100,50
    //      2           3
    //0, 100    50,100      100, 100
    std::cout << "Hello World!\n";
}
