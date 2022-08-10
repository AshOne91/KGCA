#include "TNode.h"

TNode::TNode(TNode* pParent, TRect rt)
{
	if (pParent != nullptr)
	{
		_depth = pParent->_depth + 1;
	}
	_rt = rt;
	_bLeaf = false;
	_pChild.resize(4);
}

void TNode::CreateChildNode(TNode* pParent)
{
	TRect rt = pParent->_rt;
	float halfW = rt.right / 2.0f;
	float halfH = rt.bottom / 2.0f;
	_pChild[0] = new TNode(pParent, { rt.left, rt.top, halfW, halfH });
	_pChild[1] = new TNode(pParent, { rt.left + halfW, rt.top, halfW, halfH });
	_pChild[2] = new TNode(pParent, { rt.left, rt.top + halfH, halfW, halfH });
	_pChild[3] = new TNode(pParent, { rt.left + halfW, rt.top + halfH, halfW, halfH });
}

TNode::~TNode()
{
	delete _pChild[0];
	delete _pChild[1];
	delete _pChild[2];
	delete _pChild[3];
}