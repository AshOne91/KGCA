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
			return pNewData;
		}
	}
	delete pNewData;
	return nullptr;
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

W_STR TextureManager::GetSplitName(std::wstring fullpath)
{
	W_STR name;
	TCHAR drive[MAX_PATH] = { 0, };
	TCHAR dir[MAX_PATH] = { 0, };
	TCHAR filename[MAX_PATH] = { 0, };
	TCHAR ext[MAX_PATH] = { 0, };
	_tsplitpath_s(fullpath.c_str(),
		drive, dir, filename, ext);
	name = filename;
	name += ext;
	return name;
}

W_STR TextureManager::GetSplitName(std::string fullpath)
{
	W_STR szUnicode = to_mw(fullpath);
	TCHAR drive[MAX_PATH] = { 0, };
	TCHAR dir[MAX_PATH] = { 0, };
	TCHAR filename[MAX_PATH] = { 0, };
	TCHAR ext[MAX_PATH] = { 0, };
	_tsplitpath_s(szUnicode.c_str(), drive, dir, filename, ext);
	W_STR fileName = filename;
	W_STR fileExt = ext;
	if (fileExt == L".tga" || fileExt == L".TGA")
	{
		fileExt = L".dds";
	}
	fileName += fileExt;
	return fileName;
}

TextureManager::TextureManager()
{
	
}

TextureManager::~TextureManager()
{
	Release();
}