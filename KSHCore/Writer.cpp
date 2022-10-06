#include "Writer.h"

bool Writer::Init()
{
	HRESULT hr;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_pd2dFactory);
	if (FAILED(hr))
	{
		return false;
	}

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_pd2dFactory);
	if (FAILED(hr))
	{
		return false;
	}

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		(IUnknown**)&_pdWriteFactory);
	if (FAILED(hr))
	{
		return false;
	}

	hr = _pdWriteFactory->CreateTextFormat(
		L"고딕",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		30,
		L"en-us",
		&_pTextFormat);
	if (FAILED(hr))
	{
		return false;
	}

	_szDefaultText = L"KGCA Game Academy";
	return true;
}

bool Writer::Init(std::wstring& font, int size)
{
	HRESULT hr;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_pd2dFactory);
	if (FAILED(hr))
	{
		return false;
	}

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_pd2dFactory);
	if (FAILED(hr))
	{
		return false;
	}

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		(IUnknown**)&_pdWriteFactory);
	if (FAILED(hr))
	{
		return false;
	}

	hr = _pdWriteFactory->CreateTextFormat(
		font.c_str(),
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		size,
		L"en-us",
		&_pTextFormat);
	if (FAILED(hr))
	{
		return false;
	}

	_szDefaultText = L"KGCA Game Academy";
	return true;
}

bool Writer::Frame()
{
	return true;
}

bool Writer::Render()
{
	Draw(0, 0, _szDefaultText, { 1, 0, 0, 1 });
	return true;
}

bool Writer::Release()
{
	if (_pd2dFactory) _pd2dFactory->Release();
	if (_pdWriteFactory) _pdWriteFactory->Release();
	if (_pd2dRT) _pd2dRT->Release();
	if (_pTextFormat) _pTextFormat->Release();
	if (_pTextColor) _pTextColor->Release();
	_pd2dFactory = nullptr;
	_pdWriteFactory = nullptr;
	_pd2dRT = nullptr;
	_pTextFormat = nullptr;
	_pTextColor = nullptr;
	return true;
}

bool Writer::Set(IDXGISurface1* dxgiSurface)
{
	// 중요 : 디바이스 생성 플래그 지정해야 한다. 
	// UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	// 3d -> 2D 연동
	D2D1_RENDER_TARGET_PROPERTIES props;
	ZeroMemory(&props, sizeof(props));
	props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	props.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
	props.dpiX = 96;
	props.dpiY = 96;
	props.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	props.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

	HRESULT hr = _pd2dFactory->CreateDxgiSurfaceRenderTarget(
		dxgiSurface,
		&props,
		&_pd2dRT
	);

	if (FAILED(hr))
	{
		return false;
	}

	hr = _pd2dRT->CreateSolidColorBrush({ 0, 0, 0, 1 }, &_pTextColor);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool Writer::Draw(float x, float y, const std::wstring& text, D2D1_COLOR_F color)
{
	_pd2dRT->BeginDraw();

	D2D1_RECT_F rt = { x, y, g_rtClient.right, g_rtClient.bottom };
	_pTextColor->SetColor(color);
	_pTextColor->SetOpacity(1.0f);
	_pd2dRT->DrawText(text.c_str(), text.size(), _pTextFormat, rt, _pTextColor);

	_pd2dRT->EndDraw();
	return true;
}