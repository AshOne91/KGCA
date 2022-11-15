#pragma once
#include "Object3D.h"
#include "Map.h"

class Node
{
public:
	int _iDepth;
	bool _bLeaf;
	DWORD _Corner[4];
	Rect _rt;
	DWORD _dwFace;
	K_BOX _kBox;
	std::vector<DWORD> _IndexList;
	ID3D11Buffer* _pIndexBuffer;
	std::vector<Node*> _pChild;
	std::vector<Object3D*> _pStaticobjectlist;
	std::vector<Object3D*> _pDynamicObjectlist;

public:
	void CreateChildNode(Node* pParent, Map* pMap, DWORD dwNumCols, DWORD dwNumRows);
	void CreateIndexData(Map* pMap, DWORD dwNumRows, DWORD dNumCols);
	HRESULT CreateIndexBuffer(Map* pMap, DWORD dwNumRows, DWORD dwNumCols);

public:
	Node(Node* pParent, Map* pMap, DWORD dwLT, DWORD dwRT, DWORD dwRB, DWORD dwLB, DWORD dwRows, DWORD dwCols);
	virtual ~Node();

};

