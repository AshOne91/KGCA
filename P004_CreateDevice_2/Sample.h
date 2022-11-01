#pragma once
#include "TWindow.h"

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
