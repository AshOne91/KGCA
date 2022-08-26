#pragma once
#include "TNode.h"
#include "TObject.h"

class TSpacePartition
{
public:
	TNode* m_pRootNode;
public:
	virtual void    AddStaticObject(TObject* pObj);
	virtual void    AddDynamicObject(TObject* pObj);
	virtual void   DynamicObjectReset(TNode* pNode);
public:
	TSpacePartition();
	virtual ~TSpacePartition();
};

