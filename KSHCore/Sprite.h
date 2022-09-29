#pragma once
#include "Object2D.h"
typedef std::vector<RECT>  RECT_ARRAY;

class Sprite : public Object2D
{
public:
	RECT_ARRAY _uvArray;
	std::vector<W_STR> _texArray;
	std::vector<Texture*> _pTexArray;
	std::vector<Sprite*> _pChild;

public:
	virtual bool Load(ID3D11Device* pd3dDevice,// 디바이스 객체
		ID3D11DeviceContext* pImmediateContext, const std::wstring& name);
};

class SpriteTexture : public Sprite
{
public:
	virtual bool Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, const std::wstring& name);
};

