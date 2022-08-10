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
	std::vector<TObject*> _pStaticObjectlist;//����
	std::vector<TObject*> _pDynamicObjectlist;//�ǽð� �����Ӹ��� ����� �ְ� �ؾߵȴ�.
	//std::vector<int> _pChild;// �ε����� �����ص� �ȴ�.
	//std::vector<int> _objectlist; �ε����� �����ص� �ȴ�.
public:
	TNode(TNode* pParent, TRect rt);
	void CreateChildNode(TNode* parent);
	virtual ~TNode();
};
