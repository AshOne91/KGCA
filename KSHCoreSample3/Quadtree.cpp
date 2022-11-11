#include "Quadtree.h"
#include "Collision.h"

bool Quadtree::Create(Camera* pMainCamera, Map* pMap, int iMaxDepth)
{
	_pCamera = pMainCamera;
	_pMap = pMap;
	_iMaxDepth = iMaxDepth;
	_pRootNode = new Node(nullptr, _pMap, 
		0, 
		//pMap->_dwNumRows - 1, 
		//pMap->_dwNumRows * (pMap->_dwNumColumns - 1), 
		//pMap->_dwNumRows * pMap->_dwNumColumns - 1,
		//pMap->_dwNumColumns, pMap->_dwNumRows);
		pMap->_iNumRows - 1,
		pMap->_iNumRows * (pMap->_iNumCols - 1),
		pMap->_iNumRows * pMap->_iNumCols - 1,
		pMap->_iNumCols, pMap->_iNumRows);
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
		_pLeafNodeList.push_back(pNode);
		return;
	}

	pNode->CreateChildNode(pNode, _pMap, _pMap->_iNumRows, _pMap->_iNumCols);

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

Node* Quadtree::VisibleNode(Node* pNode)
{
	K_POSITION dwRet = _pCamera->_vFrustum.ClassifyBox(pNode->_kBox);
	if (P_FRONT == dwRet)
	{
		_pDrawLeafNodeList.push_back(pNode);
		return pNode;
	}
	if (P_SPANNING == dwRet)
	{
		if (pNode->_bLeaf)
		{
			_pDrawLeafNodeList.push_back(pNode);
		}
		else
		{
			for (int iNode = 0; iNode < 4; ++iNode)
			{
				VisibleNode(pNode->_pChild[iNode]);
			}
		}
	}
}

bool Quadtree::Frame()
{
	_pDrawLeafNodeList.clear();
	VisibleNode(_pRootNode);
	/*
		for (auto node : _pLeafNodeList)
		{
			if (_pCamera->_vFrustum.ClassifyBox(node->_kBox))
			{
				_pDrawLeafNodeList.push_back(node);
			}
		}
	*/
	return true;
}

bool Quadtree::Render()
{
	for (auto node : _pDrawLeafNodeList)
	{
		_pMap->PreRender();
		_pMap->_pImmediateContext->IASetIndexBuffer(node->_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		_pMap->_pImmediateContext->DrawIndexed(node->_dwFace * 3, 0, 0);
	}
	return true;
}

Quadtree::~Quadtree()
{
	if (_pRootNode)
	{
		delete _pRootNode;
		_pRootNode = nullptr;
	}
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
