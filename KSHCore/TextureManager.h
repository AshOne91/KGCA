#pragma once
#include "Texture.h"

class TextureManager : public Singleton<TextureManager>
{
public:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);

private:
	friend class Singleton<TextureManager>;
	std::map<std::wstring, Texture*> _List;

public:
	Texture* Load(const std::wstring& name);
	Texture* Find(const std::wstring& name);
	bool Release();

private:
	TextureManager();
public:
	~TextureManager();
};

#define I_Tex TextureManager::GetInstance()

