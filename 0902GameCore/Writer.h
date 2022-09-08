#pragma once
#include "Std.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

//Direct2D 객체 생성
// 
// ID2D1Factory -> Direct2D 리소스를 생성 및 사용하기 위해서는 필수적인 객체 (멀티쓰레드를 원할 씨 열거형 추가)
// 
// IDWriteFaactory -> 높은 품질의 텍스트 렌더링 및 윤곽선 글꼴을 지원
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

