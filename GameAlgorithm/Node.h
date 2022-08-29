#pragma once
#include <vector>
#include <list>
#include "Collison.h"

class GameObject;
class Node
{
public:
	Box2D _box2D;
	Sphere _sphere;
	Box3D _box3D;
	Circle _circle;
	Node* _pParent;
	int _depth;
	std::vector<GameObject*> _objectStaticList;
	std::vector<GameObject*> _objectDynamicList;
	std::vector<Node*> _pChild;
public:
	Node();
	Node(Node* pParent, Vector2D pos, Vector2D size);
	Node(Node* pParent, Vector3D pos, Vector3D size);
	~Node();
};

