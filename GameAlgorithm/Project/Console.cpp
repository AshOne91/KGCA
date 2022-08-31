#include "Console.h"
#include <iostream>
#include <Windows.h>

Console::Console()
	:_hConsole(NULL)
	, _activeIndex(0)
{

}

Console::~Console()
{

}

void Console::Initial()
{
	system("mode con:cols=51 lines=51");
	CONSOLE_CURSOR_INFO stConsoleCursor;
	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize = 1;
	_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(_hConsole, &stConsoleCursor);
}

void Console::Sprite_Draw(int iX, int iY, char chSprite)
{
	if (iX < 0 || iX >dfSCREEN_WIDTH || iY > dfSCREEN_HEIGHT || iY < 0) return;
	_buffers[_bufferIndex][iY][iX] = chSprite;
}

void Console::MoveCursor(int posX, int posY)
{
	COORD coord;
	coord.X = posX;
	coord.Y = posY;
	SetConsoleCursorPosition(_hConsole, coord);
}

void Console::BufferFlip()
{
	int temp = _activeIndex;
	_activeIndex = _bufferIndex;
	_bufferIndex = temp;
}
void Console::BufferDraw()
{
	for (int y = 0; y < dfSCREEN_HEIGHT; ++y)
	{
		for (int x = 0; x < dfSCREEN_WIDTH; ++x)
		{
			std::cout<<_buffers[_activeIndex][y][x];
		}
		std::cout << std::endl;
	}
}
void Console::BufferClear()
{
	for (int y = 0; y < dfSCREEN_HEIGHT; ++y)
	{
		for (int x = 0; x < dfSCREEN_WIDTH; ++x)
		{
			_buffers[_bufferIndex][y][x] = ' ';
		}
	}
	MoveCursor(0, 0);
}

