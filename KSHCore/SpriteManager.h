#pragma once
#include "Sprite.h"

class SpriteManager : public Singleton<SpriteManager>
{
	static Sprite _NullSprite;
public:
	std::vector<UINT> _iSpriteTypeList;
	std::vector<W_STR> _rtNameList;
	std::vector<W_STR> _textureNameList;
	std::vector<W_STR> _maskTextureNameList;
	std::vector<W_STR> _shaderNameList;
	std::vector<RECT_ARRAY> _rtSpriteList;
	std::vector<TCHAR_STRING_VECTOR> _szSpriteList;

public:
	ID3D11Device* _pd3dDevice = nullptr;// 디바이스 객체
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);

private:
	friend class Singleton<SpriteManager>;
	std::map<std::wstring, std::unique_ptr<Sprite>> _List;
	std::vector<W_STR>  filelist;

public:
	bool GameDataLoad(const TCHAR* pszLoad);
	bool Load(std::wstring name);
	Sprite* Find(std::wstring name);
	bool	  Release();
	Sprite& Get(W_STR name);
	Sprite* GetPtr(W_STR name);

private:
	SpriteManager();
public:
	~SpriteManager();
};

#define I_Sprite SpriteManager::GetInstance()

