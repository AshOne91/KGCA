#pragma once
#include "Object2D.h"
typedef std::vector<RECT>  RECT_ARRAY;

class Sprite : public Object2D
{
public:
	W_STR			_szName;
	UINT			_IIndex;

public:
	RECT_ARRAY		_uvArray;
	std::vector<Sprite*>  _pChild;

public:
	HRESULT Load(ID3D11Device* pd3dDevice,// 디바이스 객체
		ID3D11DeviceContext* pImmediateContext, std::wstring name);
};

