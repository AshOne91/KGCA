#include "Node.h"

void Node::CreateChildNode(Node* pParent)
{
	// 0  1   2   3   4
	// 5  6   7   8   9
	// 10 11  12  13  14
	// 15 16  17  18  19
	// 20  21 22  23  24
	Rect rt = pParent->_rt;
	DWORD dwLT = pParent->_Corner[0];
	DWORD dwRT = pParent->_Corner[1];
	DWORD dwLB = pParent->_Corner[2];
	DWORD dwRB = pParent->_Corner[3];
	DWORD dwTopCenter = (dwLT + dwRT) / 2;
	DWORD dwRightCenter = (dwRB + dwRT) / 2;
	DWORD dwBottomCenter = (dwLB + dwRB) / 2;
	DWORD dwLeftCenter = (dwLB + dwLT) / 2;
	DWORD dwCenter = (dwRT + dwLT + dwRB + dwLB) / 4;
	_pChild[0] = new Node(pParent, dwLT, dwTopCenter, dwLeftCenter, dwCenter);
	_pChild[1] = new Node(pParent, dwTopCenter, dwRT, dwCenter, dwRightCenter);
	_pChild[2] = new Node(pParent, dwLeftCenter, dwCenter, dwLB, dwBottomCenter);
	_pChild[3] = new Node(pParent, dwCenter, dwRightCenter, dwBottomCenter, dwRB);
}

//  0, 1
//  2, 3
Node::Node(Node* pParent, DWORD dwLT, DWORD dwRT, DWORD dwRB, DWORD dwLB)
{
	if (pParent != nullptr)
	{
		_iDepth = pParent->_iDepth + 1;
	}
	_Corner[0] = dwLT;
	_Corner[1] = dwRT;
	_Corner[2] = dwRB;
	_Corner[3] = dwLB;
	_bLeaf = false;
	_pChild.resize(4);
}

Node::~Node()
{
	delete _pChild[0];
	delete _pChild[1];
	delete _pChild[2];
	delete _pChild[3];
	_pChild[0] = nullptr;
	_pChild[1] = nullptr;
	_pChild[2] = nullptr;
	_pChild[3] = nullptr;
}