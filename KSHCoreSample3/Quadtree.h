#pragma once
#include "Node.h"
#include "Map.h"

class Quadtree
{
public:
	Node* _pRootNode;
	int _iMaxDepth;
	Map* _pMap = nullptr;

public:
	bool Create(Map* pMap, int iMaxDepth = 2);
	bool AddObject(Object3D* pObj);
	void BuildTree(Node* pNode);
	bool IsSubDivide(Node* pNode);
	Node* FindNode(Node* pNode, Object3D* pObj);
	void Reset(Node* pNode);
};

