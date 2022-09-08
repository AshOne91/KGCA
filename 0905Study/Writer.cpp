#include "Writer.h"

bool Writer::Init()
{
    //
    // DirectWrite 객체생성
    // 
    //
    HRESULT hr;
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_d2dFactory);
    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        (IUnknown**)&_pDWriteFactory);
    hr = _pDWriteFactory->CreateTextFormat(
        L"Gabriola", //L"고딕",
        NULL,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        30,
        L"en-us",//, // L"ko-kr",//
        &_pTextFormat);
    if (FAILED(hr))
    {
        return false;
    }

    _szDefaultText = L"KGCA Game Academy";
    hr = _pDWriteFactory->CreateTextLayout(
        _szDefaultText.c_str(),
        _szDefaultText.size(),
        _pTextFormat,
        g_rtClient.right,
        g_rtClient.bottom,
        &_pTextLayout);
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

bool Writer::Frame()
{
    return true;
}

bool Writer::Render()
{
    return Draw(0, 0, _szDefaultText, { 1, 0, 0, 1 });
}

bool Writer::Release()
{
    if (_pTextLayout) _pTextLayout->Release();
    if (_pTextColor) _pTextColor->Release();
    if (_pDWriteFactory) _pDWriteFactory->Release();
    if (_d2dRT) _d2dRT->Release();
    if (_d2dFactory) _d2dFactory->Release();
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

    HRESULT hr = _d2dFactory->CreateDxgiSurfaceRenderTarget(
        dxgiSurface,
        &props,
        &_d2dRT);
    if (FAILED(hr))
    {
        return false;
    }

    hr = _d2dRT->CreateSolidColorBrush({ 0, 0, 0, 1 }, &_pTextColor);
    if (FAILED(hr))
    {
        return false;
    }
    return true;
}

bool Writer::Draw(float x, float y, std::wstring text, D2D1_COLOR_F color)
{
    _d2dRT->BeginDraw();

    D2D1_RECT_F rt = { x, y, g_rtClient.right, g_rtClient.bottom };
    _pTextColor->SetColor(color);
    _pTextColor->SetOpacity(1.0f);
    _d2dRT->DrawText(text.c_str(), text.size(), _pTextFormat, rt, _pTextColor);

    _pTextLayout->SetFontSize(50, { 0, (UINT)_szDefaultText.size() });
    _pTextLayout->SetFontStyle(DWRITE_FONT_STYLE_ITALIC, { 0, (UINT)_szDefaultText.size() });
    _d2dRT->DrawTextLayout({ 400, 300 }, _pTextLayout, _pTextColor);
    _d2dRT->EndDraw();
    return true;
}
