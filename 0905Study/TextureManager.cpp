#include "TextureManager.h"

void TextureManager::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
    _pd3dDevice = pd3dDevice;
    _pImmediateContext = pContext;
}

Texture* TextureManager::Find(const std::wstring& name)
{
    auto iter = _list.find(name);
    if (iter != _list.end())
    {
        return iter->second;
    }
    return nullptr;
}

Texture* TextureManager::Load(const std::wstring& name)
{
    HRESULT hr;
    auto data = Find(name);
    if (data != nullptr) return data;

    Texture* pNewData = new Texture;
    if (pNewData)
    {
        hr = pNewData->Load(_pd3dDevice, _pImmediateContext, name);
        if (SUCCEEDED(hr))
        {
            _list.insert(std::make_pair(name, pNewData));
        }
    }
    return pNewData;
}

bool TextureManager::Release()
{
    for (auto data : _list)
    {
        Texture* pData = data.second;
        if (pData) pData->Release();
        delete pData;
    }
    _list.clear();
    return true;
}

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
    Release();
}
