#include "ShaderManager.h"

void ShaderManager::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
    _pd3dDevice = pd3dDevice;
    _pImmediateContext = pContext;
}

Shader* ShaderManager::Load(const std::wstring& name)
{
    HRESULT hr;
    auto iter = _list.find(name);
    if (iter != _list.end())
    {
        return iter->second;
    }

    Shader* pNewData = new Shader;
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

bool ShaderManager::Release()
{
    for (auto data : _list)
    {
        Shader* pData = data.second;
        if (pData) pData->Release();
        delete pData;
    }
    _list.clear();
    return true;
}

ShaderManager::ShaderManager()
{

}

ShaderManager::~ShaderManager()
{
    Release();
}
