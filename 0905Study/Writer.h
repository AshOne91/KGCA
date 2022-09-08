#pragma once
#include "Std.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

//Direct2D ��ü ����
// 
// ID2D1Factory -> Direct2D ���ҽ��� ���� �� ����ϱ� ���ؼ��� �ʼ����� ��ü (��Ƽ�����带 ���� �� ������ �߰�)
// 
// IDWriteFaactory -> ���� ǰ���� �ؽ�Ʈ ������ �� ������ �۲��� ����
//
class Writer
{
public:
	ID2D1Factory* _d2dFactory;
	IDWriteFactory* _pDWriteFactory;
	ID2D1RenderTarget* _d2dRT;
	IDWriteTextFormat* _pTextFormat;
	ID2D1SolidColorBrush* _pTextColor;
	std::wstring _szDefaultText;

	IDWriteTextLayout* _pTextLayout;

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

public:
	bool Set(IDXGISurface1* dxgiSurface);
	bool Draw(float x, float y, std::wstring text, D2D1_COLOR_F color = { 0, 0, 0, 1 });
};

