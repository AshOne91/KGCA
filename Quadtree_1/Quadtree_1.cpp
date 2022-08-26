#include "TCollision.h"
#include "TVector.h"
std::queue<TNode*> g_Queue;
class TObject
{
public:
    TRect _rt;
    TCircle _circle;
    TVector2D _vDirection;
    void SetCircle(float x, float y, float w, float h)
    {
        _circle.cx = x;
        _circle.cy = y;
        float tempX = w / 2.0f;
        float tempY = h/ 2.0f;
        _circle.fRadius = sqrt(tempX * tempX + tempY * tempY);
    }
    void SetPosition(float x, float y, float w, float h)
    {
        _rt.Set(x, y, w, h);
        SetCircle(_rt._cx, _rt._cy, _rt._w, _rt._h);
    }
    TObject()
    {
        _rt.Set(20 + (rand() % 80), 20 + (rand() % 80), 5.0f + (rand() % 5), 5.0f + (rand() % 5));
        _vDirection.x = cos(rand());
        _vDirection.y = sin(rand());
        _vDirection.Normalized();
    }

    void Frame()
    {

    }
};
class TNode
{
public:
    TRect _rt;
    int _depth;
    std::vector<TObject*> _objectStaticlist;
    std::vector<TObject*> _objectDynamiclist;
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
    void AddStaticObject(TObject* pObj);
    void AddDynamicObject(TObject* pObj);
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
        if (TCollision::CircleToCircle(pNode->_objectList[iObj]->_circle, pSrcObject->_circle))
        {
            //노드 교차여부
            if (TCollision::RectToRect(pNode->_objectList[iObj]->_rt, pSrcObject->_rt))
            {
                list.push_back(_pRootNode->_objectList[iObj]);
            }
        }
    }
    if (pNode->_pChild[0] != nullptr)
    {
        for (int iChild = 0; iChild < 4; iChild++)
        {
            //노드 교차여부(걸쳐져만 있어도)
            if (TCollision::RectToRect(pNode->_pChild[iChild]->_rt, pSrcObject->_rt))
            {
                GetCollisionObject(pNode->_pChild[iChild], pSrcObject, list);
            }
        }
    }
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
    TObject m_player;
    m_player.SetPosition(40, 60, 10, 10);
    TQuadtree quadtree;
    quadtree.Create(100.0f, 100.0f);
    for (int i = 0; i < 10; ++i)
    {
        TObject* pObj = new TObject;
        quadtree.AddObject(pObj);
        float x = m_player._rt._x - pObj->_rt._x;
        float y = m_player._rt._y - pObj->_rt._y;
        float fDistance = sqrt(x * x + y * y);
    }
    //TNode* pNodem_player = quadtree.FindNode(quadtree._pRootNode, &m_player);
    std::vector<TObject*> list = quadtree.Collision(&m_player);
    if (!list.empty())
    {
        for (int iObj = 0; iObj < list.size(); iObj++)
        {
            std::cout << list[iObj]->_rt._x
                << list[iObj]->_rt._y << std::endl;
        }
    }

    TVector2D vPos(m_player._rt._x, m_player._rt._y);
    TVector2D vTmp = m_player._vDirection * 1.0f;
    vPos = vPos + vTmp;
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

    quadtree.AddStaticObject
    std::cout << "Hello World!\n";
}
