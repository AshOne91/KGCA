#pragma once
#include <Windows.h>
#include  <string>
#define dfSCREEN_WIDTH 50
#define dfSCREEN_HEIGHT 50

class Console
{
private:
	bool _pause = false;
	int _activeIndex = 0;
	int _bufferIndex = 1;
	HANDLE _hConsole;
	char _buffers[2][dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

public:
	Console();
	virtual ~Console();

private:
	void MoveCursor(int posX, int posY);

public:
	void Initial();
	void Sprite_Draw(int iX, int iY, char chSprite);
	void BufferFlip();
	void BufferClear();
	void BufferDraw();
};
