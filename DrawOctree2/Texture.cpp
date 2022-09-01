#include "Texture.h"

bool Texture::Init()
{
    return true;
}

bool Texture::Frame()
{
    return true;
}

bool Texture::Render()
{
    return true;
}

bool Texture::Release()
{
    if (_texture) _texture->Release();
    if (_pTextureSRV) _pTextureSRV->Release();
    _texture = nullptr;
    _pTextureSRV = nullptr;
    return true;
}

HRESULT Texture::Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, const std::wstring& name)
{
    HRESULT hr;
    _pd3dDevice = pd3dDevice;
    _pImmediateContext = pImmediateContext;
    hr = DirectX::CreateWICTextureFromFile(
        pd3dDevice,
        pImmediateContext,
        name.c_str(),
        &_texture,
        &_pTextureSRV
    );
    return hr;
}
