#include "Node.h"

QuadtreeNode::QuadtreeNode()
{

}

QuadtreeNode::QuadtreeNode(QuadtreeNode* pParent, Vector2D pos, Vector2D size)
{
	_box2D.Set(pos.x, pos.y, size.x, size.y);
	if (pParent != nullptr)
	{
		_pParent = pParent;
		_depth = pParent->_depth + 1;
	}
}

QuadtreeNode::~QuadtreeNode()
{

}

OctreeNode::OctreeNode()
{

}

OctreeNode::OctreeNode(OctreeNode* pParent, Vector3D pos, Vector3D size)
{
	_box3D.Set(pos, size);
	if (pParent != pParent)
	{
		_pParent = pParent;
		_depth = pParent->_depth + 1;
	}
}

OctreeNode::~OctreeNode()
{

}
