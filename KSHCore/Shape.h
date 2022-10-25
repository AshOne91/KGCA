#pragma once
#include "BaseObject.h"

class Shape : public BaseObject
{
public:
	Shape() {};
	virtual ~Shape() {};
};

class ShapeBox : public Shape
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

class ShapeLine : public Shape
{
public:
	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;
	virtual bool Frame() override;
	virtual bool Render() override;

public:
	ShapeLine() {};
	virtual ~ShapeLine() {};
};

class ShapeDirectionLine : public ShapeLine
{
public:
	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;

public:
	ShapeDirectionLine() {};
	virtual ~ShapeDirectionLine() {};
};