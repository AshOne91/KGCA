#include "Sample.h"
class TNode
{
public:
	int _data;
	int _depth;
	TNode* _pChild[2];
	TNode() : _data(-1), _depth(0)
	{
		_pChild[0] = nullptr;
		_pChild[1] = nullptr;
	}
	virtual ~TNode()
	{
		delete _pChild[0];
		delete _pChild[1];
	}
};

TNode* g_pRootNode = nullptr;
int g_iMaxDepth = 3;
int main()
{
	g_pRootNode = new TNode;
}
