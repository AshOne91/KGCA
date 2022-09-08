#pragma once
#include "Std.h"

enum KeyState
{
	KEY_FREE = 0,
	KEY_UP,
	KEY_PUSH,
	KEY_HOLD
};

class Input : public Singleton<Input>
{
private:
	DWORD _dwKeyState[256];
public:
	POINT _ptPos;

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

public:
	DWORD GetKey(DWORD dwKey);
};

#define I_Input Input::GetInstance()

