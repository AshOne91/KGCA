#include "TextureManager.h"

void TextureManager::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pContext;
}

Texture* TextureManager::Load(const std::wstring& name)
{
	auto data = Find(name);
	if (data != nullptr) return data;

	Texture* pNewData = new Texture;
	if (pNewData)
	{
		HRESULT hr;
		hr = pNewData->Load(_pd3dDevice, _pImmediateContext, name);
		if (SUCCEEDED(hr))
		{
			_List.insert(std::make_pair(name, pNewData));
		}
	}

	return pNewData;
}

Texture* TextureManager::Find(const std::wstring& name)
{
	auto iter = _List.find(name);
	if (iter != _List.end())
	{
		return iter->second;
	}
	return nullptr;
}

bool TextureManager::Release()
{
	for (auto& data : _List)
	{
		Texture* pTexture = data.second;
		if (pTexture) pTexture->Release();
		delete pTexture;
	}
	_List.clear();
	return true;
}

TextureManager::TextureManager()
{
	
}

TextureManager::~TextureManager()
{
	Release();
}