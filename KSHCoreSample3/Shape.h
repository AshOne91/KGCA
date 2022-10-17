#pragma once
#include "BaseObject.h"

class Object3D : public BaseObject
{
public:
	Object3D() {};
	virtual ~Object3D() {};
};

class Shape : public Object3D
{
public:
	Shape() {};
	virtual ~Shape() {};
};

class ShapeBox : public Object3D
{
public:
	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;
	virtual bool Frame() override;
	virtual bool Render() override;

public:
	ShapeBox() {};
	virtual ~ShapeBox() {}
};

