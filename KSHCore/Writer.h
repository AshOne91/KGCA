#pragma once
#include "Std.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

class Writer
{
public:
	ID2D1Factory* _pd2dFactory = nullptr;
	IDWriteFactory* _pdWriteFactory = nullptr;
	ID2D1RenderTarget* _pd2dRT = nullptr;
	IDWriteTextFormat* _pTextFormat = nullptr;
	ID2D1SolidColorBrush* _pTextColor = nullptr;
	std::wstring _szDefaultText;

public:
	virtual bool Init();
	virtual bool Init(std::wstring& font, int size);
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

public:
	bool Set(IDXGISurface1* dxgiSurface);
	bool Draw(float x, float y, const std::wstring& text, D2D1_COLOR_F color = { 0.0f, 0.0f, 0.0f, 1.0f });
};

