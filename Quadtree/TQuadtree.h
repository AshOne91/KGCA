#pragma once
#include "TNode.h"
#include "TShape.h"
class TQuadtree
{
public:
	TNode* _pRootNode;
	int _maxDepth;
public:
	bool Create(TRect rt, int maxDepth = 2);
	void Reset(TNode* pNode);
	TNode* FindNode(TNode* pNode, TObject* pObj);
	bool AddObject(TObject* pObj);
	void BuildTree(TNode* pNode);
	bool IsSubDivide(TNode* pNode);
};