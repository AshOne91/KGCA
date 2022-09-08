#pragma once
#include "BaseObject.h"
#include "GameCore.h"
class Sample : public GameCore
{
private:
	std::vector<BaseObject*> _pObjectList;
	int _iTexIndex = 0;
public:
	virtual bool Init() final;
	virtual bool Frame() final;
	virtual bool Render() final;
	virtual bool Release() final;
};

