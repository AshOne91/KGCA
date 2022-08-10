#pragma once
#include "TObject.h"
#include "TShape.h"
class TNode
{
public:
	int _depth;
	bool _bLeaf;
	TRect _rt;
	std::vector<TNode*> _pChild;
	std::vector<TObject*> _pObjectlist;
	std::vector<TObject*> _pStaticObjectlist;//정적
	std::vector<TObject*> _pDynamicObjectlist;//실시간 프레임마다 지우고 넣고 해야된다.
	//std::vector<int> _pChild;// 인덱스로 관래해도 된다.
	//std::vector<int> _objectlist; 인덱스로 관리해도 된다.
public:
	TNode(TNode* pParent, TRect rt);
	void CreateChildNode(TNode* parent);
	virtual ~TNode();
};
