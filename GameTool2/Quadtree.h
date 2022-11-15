#pragma once
#include "Node.h"

class Quadtree
{
public:
	Node* _pRootNode;
	int _iMaxDepth;
	Map* _pMap = nullptr;
	Camera* _pCamera = nullptr;
	std::vector<Node*> _pLeafNodeList;
	std::vector<Node*> _pDrawLeafNodeList;

public:
	bool Create(Camera* pMainCamera, Map* pMap, int iMaxDepth = 3);
	bool AddObject(Object3D* pObj);
	void BuildTree(Node* pNode);
	bool IsSubDivide(Node* pNode);
	Node* FindNode(Node* pNode, Object3D* pObj);
	void Reset(Node* pNode);
	bool Frame();
	bool Render();
	Node* VisibleNode(Node* pNode);
	virtual ~Quadtree();
};

