#pragma once
#include <vector>
#include <list>
#include "Collison.h"

class GameObject;
class Node abstract
{
protected:
	Node* _pParent;
	int _depth;
	std::vector<GameObject*> _objectStatickList;
	std::vector<GameObject*> _objectDynamicList;
	std::vector<Node*> _pChild;
public:
	Node() :_pParent(nullptr), _depth(0)
	{ 
	};
	virtual ~Node()
	{
		for (int iChild = 0; iChild < _pChild.size(); ++iChild)
		{
			delete _pChild[iChild];
		}
	}
};

class QuadtreeNode : public Node
{
private:
	Box2D _box2D;
	Sphere _sphere;
public:
	QuadtreeNode();
	QuadtreeNode(QuadtreeNode* parent, Vector2D pos, Vector2D size);
	virtual ~QuadtreeNode();

public:

};

class OctreeNode : public Node
{
private:
	Box3D _box3D;
	Circle _circle;
public:
	OctreeNode();
	OctreeNode(OctreeNode* parent, Vector3D pos, Vector3D size);
	virtual ~OctreeNode();
};

/*class QuadTreeObject abstract
{
public:
	virtual Circle* GetCircle() = 0;
	virtual Box2D* GetBox2D() = 0;
	virtual QuadtreeNode* GetNode() = 0;
	virtual void SetNode(QuadtreeNode* pNode) = 0;
};

class OctreeObject abstract
{
public:
	virtual Sphere* GetSphere() = 0;
	virtual Box3D* GetBox3D() = 0;
	virtual OctreeNode* GetNode() = 0;
	virtual void SetNode(OctreeNode* pNode) = 0;
};*/

