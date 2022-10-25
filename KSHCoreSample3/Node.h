#pragma once
#include "Object3D.h"

class Node
{
public:
	int _iDepth;
	bool _bLeaf;
	DWORD _Corner[4];
	Rect _rt;
	std::vector<Node*> _pChild;
	std::vector<Object3D*> _pStaticobjectlist;
	std::vector<Object3D*> _pDynamicObjectlist;

public:
	void CreateChildNode(Node* pParent);

public:
	Node(Node* pParent, DWORD dwLT, DWORD dwRT, DWORD dwRB, DWORD dwLB);
	virtual ~Node();

};

