#pragma once
#include "GameCore.h"

class Sample : public GameCore
{
public:
	virtual bool Init() final;
	virtual bool Frame() final;
	virtual bool Render() final;
	virtual bool Release() final;
};
