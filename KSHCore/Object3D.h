#pragma once
#include "Shape.h"

class Object3D : public BaseObject
{
public:
	W_STR _csName;

public:
	Vector3D _vPos;
	Vector3D _vLook; // z axis
	Vector3D _vUp;	 // y
	Vector3D _vRight;// z
	K_BOX _BoxCollision;

public:
	Object3D() {}
	virtual ~Object3D() {}
	void UpdateCollision();
	void GenAABB();
};

class ObjectBox : public Object3D
{
public:
	Shape* _pDirLineShape = nullptr;

public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
	virtual void SetMatrix(Matrix* matWorld, Matrix* matView, Matrix* matProj);

public:
	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;

public:
	ObjectBox() {}
	virtual ~ObjectBox() {}
};
