#pragma once
#include "Shape.h"

class Object3D : public BaseObject
{
public:
	W_STR _szName;

public:
	TVector3 _vPos;
	TVector3 _vLook; // z axis
	TVector3 _vUp;	 // y
	TVector3 _vRight;// z
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
	virtual void SetMatrix(TMatrix* matWorld, TMatrix* matView, TMatrix* matProj);

public:
	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;

public:
	ObjectBox() {}
	virtual ~ObjectBox() {}
};
