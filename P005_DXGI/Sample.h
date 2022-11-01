#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "TWindow.h"
#include "TEnumeration.h"
class Sample : public TWindow
{

public:
	bool		Init();
	bool		Render();
	bool		Release();
public:
	Sample(void);
	~Sample(void);
};
