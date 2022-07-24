#include "ConsoleManager.h"
#include <iostream>
#include <Windows.h>

ConsoleManager::ConsoleManager()
	:_hConsole(NULL)
	, _activeIndex(0)
{

}

ConsoleManager::~ConsoleManager()
{

}

void ConsoleManager::Initial()
{
	CONSOLE_CURSOR_INFO stConsoleCursor;
	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize = 1;
	_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(_hConsole, &stConsoleCursor);
}

void ConsoleManager::MoveCursor(int posX, int posY)
{
	COORD coord;
	coord.X = posX;
	coord.Y = posY;
	SetConsoleCursorPosition(_hConsole, coord);
}

void ConsoleManager::BufferDraw()
{
	std::cout << _buffers[_activeIndex];
}

void ConsoleManager::BufferFlip()
{
	if (_buffers[_bufferIndex].size() > 0)
	{
		int temp = _activeIndex;
		_activeIndex = _bufferIndex;
		_bufferIndex = temp;
	}
}

void ConsoleManager::BufferClear()
{
	_buffers[_activeIndex].clear();
	MoveCursor(0, 0);
}

void ConsoleManager::DoUpdate()
{
	if (_pause == false)
	{
		BufferClear();
		BufferFlip();
		BufferDraw();
	}
}

void ConsoleManager::SetBuffer(std::string& console)
{
	_buffers[_bufferIndex] = console;
}

void ConsoleManager::ConsoleClear()
{
	MoveCursor(0, 0);
	_buffers[0].clear();
	_buffers[1].clear();
	system("cls");
}

void ConsoleManager::Pause()
{
	_pause = true;
}

void ConsoleManager::Resume()
{
	_pause = false;
}

void ConsoleManager::OnEnable()
{
	AppSubSystem::OnEnable();
}

void ConsoleManager::OnDisable()
{
	AppSubSystem::OnDisable();
}

void ConsoleManager::Construct()
{
	AppSubSystem::Construct();
	Initial();
}

void ConsoleManager::Destruct()
{
	CloseHandle(_hConsole);
	AppSubSystem::Destruct();
}

bool ConsoleManager::OnMessage(BaseObject* sender, const std::string& message)
{
	if (AppSubSystem::OnMessage(sender, message) == true)
	{
		return true;
	}

	return false;
}

