#pragma once
#include "TWindow.h"
class Sample : public TWindow
{
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

