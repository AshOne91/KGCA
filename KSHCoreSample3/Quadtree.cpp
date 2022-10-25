#include "Quadtree.h"
#include "Collision.h"

bool Quadtree::Create(Map* pMap, int iMaxDepth)
{
	_pMap = pMap;
	_iMaxDepth = iMaxDepth;
	_pRootNode = new Node(nullptr, 
		0, 
		pMap->_dwNumRows - 1, 
		pMap->_dwNumRows * (pMap->_dwNumColumns - 1), 
		pMap->_dwNumRows * pMap->_dwNumColumns - 1);
	BuildTree(_pRootNode);
	return true;
}

bool Quadtree::AddObject(Object3D* pObj)
{
	Node* pFindNode = FindNode(_pRootNode, pObj);
	if (pFindNode != nullptr)
	{
		pFindNode->_pDynamicObjectlist.push_back(pObj);
		return true;
	}
	return false;
}

void Quadtree::BuildTree(Node* pNode)
{
	if (pNode == nullptr)
	{
		return;
	}
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

bool Quadtree::IsSubDivide(Node* pNode)
{
	if ((pNode->_Corner[1] - pNode->_Corner[0]) == 1)
	{
		return false;
	}
	if (pNode->_iDepth < _iMaxDepth)
	{
		return true;
	}
	return false;
}

Node* Quadtree::FindNode(Node* pNode, Object3D* pObj)
{
	for (int i = 0; i < 4; ++i)
	{
		if (pNode->_pChild[i] != nullptr)
		{

		}
	}
	return pNode;
}

void Quadtree::Reset(Node* pNode)
{
	if (pNode == nullptr)
	{
		return;
	}
	Reset(pNode->_pChild[0]);
	Reset(pNode->_pChild[1]);
	Reset(pNode->_pChild[2]);
	Reset(pNode->_pChild[3]);
}
