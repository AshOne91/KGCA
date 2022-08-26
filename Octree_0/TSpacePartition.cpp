#include "TSpacePartition.h"

void TSpacePartition::AddStaticObject(TObject* pObj)
{
}

void TSpacePartition::AddDynamicObject(TObject* pObj)
{
}

void TSpacePartition::DynamicObjectReset(TNode* pNode)
{
}

TSpacePartition::TSpacePartition()
{
}

TSpacePartition::~TSpacePartition()
{
	delete m_pRootNode;
	m_pRootNode = nullptr;
}
