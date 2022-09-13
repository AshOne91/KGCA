#include "ShaderManager.h"

void ShaderManager::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pContext;
}

Shader* ShaderManager::Load(const std::wstring& name)
{
    HRESULT hr;
    auto iter = _List.find(name);
    if (iter != _List.end())
    {
        return iter->second;
    }
    Shader* pNewData = new Shader;
    if (pNewData)
    {
        hr = pNewData->Load(_pd3dDevice, _pImmediateContext, name);
        if (SUCCEEDED(hr))
        {
            _List.insert(std::make_pair(name, pNewData));
        }
    }
    return pNewData;
}

Shader* ShaderManager::VLoad(const std::wstring& name, std::string funName)
{
    HRESULT hr;
    std::wstring vName = name;
    vName += mtw(funName);
    auto iter = _List.find(vName);
    if (iter != _List.end())
    {
        return iter->second;
    }
    Shader* pNewData = new Shader;
    if (pNewData)
    {
        hr = pNewData->Load(_pd3dDevice, _pImmediateContext, name);
        if (SUCCEEDED(hr))
        {
            _List.insert(std::make_pair(name, pNewData));
        }
    }
    return pNewData;
}

Shader* ShaderManager::PLoad(const std::wstring& name, std::string funName)
{
    HRESULT hr;
    std::wstring vName = name;
    vName += mtw(funName);
    auto iter = _List.find(vName);
    if (iter != _List.end())
    {
        return iter->second;
    }
    Shader* pNewData = new Shader;
    if (pNewData)
    {
        hr = pNewData->Load(_pd3dDevice, _pImmediateContext, name);
        if (SUCCEEDED(hr))
        {
            _List.insert(std::make_pair(name, pNewData));
        }
    }
    return pNewData;
}

bool ShaderManager::Release()
{
    for (auto data : _List)
    {
        Shader* pData = data.second;
        if (pData) pData->Release();
        delete pData;
    }
    _List.clear();
    return true;
}

ShaderManager::ShaderManager()
{

}

ShaderManager::~ShaderManager()
{
    Release();
}
