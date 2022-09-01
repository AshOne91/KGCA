#pragma once
#include "Device.h"
#include "BaseObject.h"
class Sample : public Device
{
private:
	std::vector<BaseObject*> _pObjectList;
	int _iTexIndex = 0;
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};

