#pragma once
#include "Device.h"
#include "Writer.h"

class GameCore : public Device
{
public:
	bool _bGameRun = true;
	Writer _writer;
	IDXGISurface1* _pBackBuffer;

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
	bool Run();
};

