#pragma once
#include <GameCore.h>

class Sample : public GameCore
{
private:
	Sound* _pBGSound = nullptr;
	Sound* _pShot = nullptr;
	Sound* _pEffect = nullptr;

public:
	virtual bool Init() final;
	virtual bool Frame() final;
	virtual bool Render() final;
	virtual bool Release() final;
};
