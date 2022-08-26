#pragma once
#include "TSpacePartition.h"

class TQuadtree : public TSpacePartition
{
public:
    std::vector<TObject*> Collision(TObject* pObj);
    void    Create(float fWidth, float fHeight);
    TNode* CreateNode(TNode* pParent,
        float fPosX, float fPosY,
        float fWidth, float fHeight);
    void    Buildtree(TNode* pNode);

    TNode* FindNode(TNode* pNode, TObject* pObj);
    void    GetCollisitionObject(TNode* pNode,
        TObject* obj,
        std::vector<TObject*>& list);

public:
    void    AddStaticObject(TObject* pObj) override;
    void    AddDynamicObject(TObject* pObj) override;
    void   DynamicObjectReset(TNode* pNode) override;
public:
    TQuadtree();
    virtual ~TQuadtree();
};