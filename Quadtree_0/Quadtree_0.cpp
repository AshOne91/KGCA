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
    void SetPosition(float x, float y, float w, float h)
    {
        _x = x;
        _y = y;
        _w = w;
        _h = h;
    }
    TObject()
    {

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
    std::vector<TObject*> Collision(TObject* pObj);
    void Create(float width, float height);
    TNode* CreateNode(TNode* pParent,
        float fPosX, float fPosY, float fWidth, float fHeight);
    void Buildtree(TNode* pNode);
    void AddObject(TObject* pObj);
    TNode* FindNode(TNode* pNode, TObject* pObj);
    bool RectToInRect(TNode* pNode, TObject* pObj);
    int RectToRect(TNode* pNode, TObject* pObj);
    int RectToRect(TObject* pDestObj, TObject* pSrcObj);
    void GetCollisionObject(TNode* pNode, TObject* pObj, std::vector<TObject*>&);
    ~TQuadtree()
    {
        delete _pRootNode;
    }
};
int TQuadtree::RectToRect(TObject* pDestObj, TObject* pSrcObj)
{
    // 0 완전제외(0)
    // 1 완전포함(1) -> 걸쳐져 있는 상태(2)
    // x1(10)----30----x2(40)
    float x1 = pDestObj->_x;
    float y1 = pDestObj->_y;
    float x2 = pDestObj->_x + pDestObj->_w;
    float y2 = pDestObj->_y + pDestObj->_h;

    float z1 = pSrcObj->_x;
    float w1 = pSrcObj->_y;
    float z2 = pSrcObj->_x + pSrcObj->_w;
    float w2 = pSrcObj->_y + pSrcObj->_h;

    // 합집합
    float fMinX; float fMinY;
    float fMaxX; float fMaxY;
    fMinX = x1 < z1 ? x1 : z1;
    fMinY = y1 < w1 ? y1 : w1;
    fMaxX = x2 < z2 ? x2 : z2;
    fMaxY = y2 < w2 ? y2 : w2;

    // 가로 판정
    if ((pDestObj->_w + pSrcObj->_w) > (fMaxX - fMinX))
    {
        //세로 판정
        if ((pDestObj->_h + pSrcObj->_h) > (fMaxY - fMinY))
        {
            //교차한다.// 교집합
            return 1;
        }
    }
    return 0;
}
int TQuadtree::RectToRect(TNode* pNode, TObject* pObj)
{
    // 0 완전제외(0)
    // 1 완전포함(1) -> 걸쳐져 있는 상태(2)
    // x1(10)----30----x2(40)
    float x1 = pNode->_x;
    float y1 = pNode->_y;
    float x2 = pNode->_x + pNode->_w;
    float y2 = pNode->_y + pNode->_h;

    float z1 = pObj->_x;
    float w1 = pObj->_y;
    float z2 = pObj->_x + pObj->_w;
    float w2 = pObj->_y + pObj->_h;

    // 합집합
    float fMinX; float fMinY;
    float fMaxX; float fMaxY;
    fMinX = x1 < z1 ? x1 : z1;
    fMinY = y1 < w1 ? y1 : w1;
    fMaxX = x2 > z2 ? x2 : z2;
    fMaxY = y2 > w2 ? y2 : w2;

    // 가로 판정
    if ((pNode->_w + pObj->_w) > (fMaxX - fMinX))
    {
        //세로 판정
        if ((pNode->_h + pObj->_h) > (fMaxY - fMinY))
        {
            //교차한다.// 교집합
            return 1;
        }
    }

    return 0;
}
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
        //노드 교차여부
        if (RectToRect(pNode->_objectList[iObj], pSrcObject))
        {
            list.push_back(_pRootNode->_objectList[iObj]);
        }
    }
    if (pNode->_pChild[0] != nullptr)
    {
        for (int iChild = 0; iChild < 4; iChild++)
        {
            //노드 교차여부(걸쳐져만 있어도)
            if (RectToRect(pNode->_pChild[iChild], pSrcObject))
            {
                GetCollisionObject(pNode->_pChild[iChild], pSrcObject, list);
            }
        }
    }
}
bool TQuadtree::RectToInRect(TNode* pNode, TObject* pObj)
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
                bool bIn = RectToInRect(pNode->_pChild[iNode], pObj);
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
    TObject m_player;
    m_player.SetPosition(40, 60, 10, 10);
    TQuadtree quadtree;
    quadtree.Create(100.0f, 100.0f);
    for (int i = 0; i < 10; ++i)
    {
        TObject* pObj = new TObject;
        quadtree.AddObject(pObj);
    }
    //TNode* pNodem_player = quadtree.FindNode(quadtree._pRootNode, &m_player);
    std::vector<TObject*> list = quadtree.Collision(&m_player);
    if (!list.empty())
    {
        for (int iObj = 0; iObj < list.size(); iObj++)
        {
            std::cout << pNodem_player->_objectList[iObj]->_x 
                << pNodem_player->_objectList[iObj]->_y << std::endl;
        }
    }

    //while (true)
    //{
        //quadtree.MoveObject();
    //}
    //화면좌표계
    //0,0 -> x   50,0       100(x), 0(y)
    //|     0           1
    //y 0,50    50,50       100,50
    //      2           3
    //0, 100    50,100      100, 100
    std::cout << "Hello World!\n";
}
