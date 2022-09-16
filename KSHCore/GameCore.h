#pragma once
#include "Device.h"
#include "Timer.h"
#include "Input.h"
#include "Writer.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"
class GameCore : public Device
{
public:
	Writer _Writer;
	ID3D11SamplerState* _pDefaultSS = nullptr;
	bool _bGameRun = true;

public:
	virtual bool Init() override { return true; }
	virtual bool Frame()  override { return true; }
	virtual bool Render()  override { return true; }
	virtual bool Release()  override { return true; }

private:
	bool CoreInit();
	bool CoreFrame();
	bool CorePreRender();
	bool CoreRender();
	bool CorePostRender();
	bool CoreRelease();

public:
	virtual bool Run() final;
};

