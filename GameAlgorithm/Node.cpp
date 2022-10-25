#include "..\KSHCoreSample3\Node.h"
#include "..\KSHCoreSample3\Node.h"
#include "Node.h"

Node::Node() :_pParent(nullptr), _depth(0)
{
}

Node::Node(Node* pParent, Vector2D pos, Vector2D size) :_pParent(nullptr), _depth(0)
{
	_box2D.Set(pos.x, pos.y, size.x, size.y);
	_circle.Set(_box2D);
	if (pParent != nullptr)
	{
		_pParent = pParent;
		_depth = pParent->_depth + 1;
	}
}

Node::Node(Node* pParent, Vector3D pos, Vector3D size):_pParent(nullptr), _depth(0)
{
	_box3D.Set(pos, size);
	_sphere.Set(_box3D);
	if (pParent != nullptr)
	{
		_pParent = pParent;
		_depth = pParent->_depth + 1;
	}
}

Node::~Node()
{
	for (int iChild = 0; iChild < _pChild.size(); ++iChild)
	{
		delete _pChild[iChild];
	}
}
