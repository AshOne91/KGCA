#include "TQuadtree.h"
#include "TCollision.h"

bool TQuadtree::Create(TRect rt, int maxDepth)
{
	_maxDepth = maxDepth;
	_pRootNode = new TNode(nullptr, rt);
	BuildTree(_pRootNode);
	return true;
}
TNode* TQuadtree::FindNode(TNode* pNode, TObject* pObj)
{
	if (pNode == nullptr) return nullptr;
	bool bFlag = true;
	if (!TCollision::RectToInRect(pNode->_rt, pObj->_rt))
	{
		return pNode;
	}
	for (int i = 0; i < 4; ++i)
	{
		if (pNode->_pChild[i] != nullptr)
		{
			if (TCollision::RectToInRect(pNode->_rt, pObj->_rt))
			{
				pNode = FindNode(pNode->_pChild[i], pObj);
				break;
			}
		}
	}
	return pNode;
}
bool TQuadtree::AddObject(TObject* pObj)
{
	TNode* pFindNode = FindNode(_pRootNode, pObj);
	if (pFindNode != nullptr)
	{
		pFindNode->_pObjectlist.push_back(pObj);
		return true;
	}
	return false;
}

void TQuadtree::BuildTree(TNode* pNode)
{
	if (pNode == nullptr) return;
	if (IsSubDivide(pNode) == false)
	{
		pNode->_bLeaf = true;
		return;
	}
	pNode->CreateChildNode(pNode);

	BuildTree(pNode->_pChild[0]);
	BuildTree(pNode->_pChild[1]);
	BuildTree(pNode->_pChild[2]);
	BuildTree(pNode->_pChild[3]);
}

void TQuadtree::Reset(TNode* pNode)
{
	if (pNode == nullptr) return;
	pNode->_pDynamicObjectlist.clear();
	if (IsSubDivide(pNode) == false)
	{
		pNode->_bLeaf = true;
		return;
	}
	pNode->CreateChildNode(pNode);

	Reset(pNode->_pChild[0]);
	Reset(pNode->_pChild[1]);
	Reset(pNode->_pChild[2]);
	Reset(pNode->_pChild[3]);
}

bool TQuadtree::IsSubDivide(TNode* pNode)
{
	if (pNode->_depth < 2)
	{
		return true;
	}
	return false;
}