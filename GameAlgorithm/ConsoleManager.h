#pragma once
#include <Windows.h>
#include  <string>
#include "AppSubSystem.h"

class ConsoleManager : public AppSubSystem<ConsoleManager>
{
private:
	bool _pause = false;
	int _activeIndex = 0;
	int _bufferIndex = 1;
	HANDLE _hConsole;
	std::string _buffers[2];

public:
	ConsoleManager();
	virtual ~ConsoleManager();

private:
	void Initial();
	void MoveCursor(int posX, int posY);
	void BufferDraw();
	void BufferFlip();
	void BufferClear();

public:
	void SetBuffer(std::string& console);
	void ConsoleClear();
	void Pause();
	void Resume();

public:
	virtual void DoUpdate();

public:
	virtual void OnEnable();
	virtual void OnDisable();

public:
	virtual void Construct();
	virtual void Destruct();

public:
	virtual bool OnMessage(BaseObject* sender, const std::string& message);
};
