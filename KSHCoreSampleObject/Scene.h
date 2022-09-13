#pragma once
#include "MapObject.h"
#include "User2D.h"
#include "Npc2D.h"

class Scene
{
public:
	ID3D11Device* _pd3dDevice = nullptr;// 디바이스 객체
	ID3D11DeviceContext* _pImmediateContext = nullptr;
public:
	User2D* _pUser;
	MapObject* _pMap;
	std::vector<BaseObject*>	_pNpcList;
	std::vector<Texture*>		_ObjectTextureList;
public:
	virtual bool		Create(
		ID3D11Device* pd3dDevice,// 디바이스 객체
		ID3D11DeviceContext* pImmediateContext,
		std::wstring shadername);
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
};

