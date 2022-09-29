#pragma once
#include "MapObject.h"
#include "User2D.h"
#include "Npc2D.h"

class Scene
{
public:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

public:
	Vector2D _vCamera = { 0,0 };
	User2D* _pUser;
	Rect _rtMap = { -1000.0f, -1000.0f, 2000.0f, 2000.0f };

public:
	virtual bool Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring shadername);
	virtual void		DrawMiniMap(UINT x, UINT y, UINT w = 100, UINT h = 100)
	{}

public:
	virtual bool		IsNextScene() { return false; }
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
};

