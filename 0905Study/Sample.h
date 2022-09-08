#pragma once
#include "BaseObject.h"
#include "GameCore.h"
#include "Collision.h"

class Object2D : public BaseObject
{
public:
	Texture* _pMaskTex = nullptr;
	POINT _ptImageSize;
	Rect _rtInit;
	Rect _rtUV;
	Vector2D _vPos;
	Vector2D _vDir;
	float _fSpeed = 100.0f;

private:
	Vector2D _vDrawPos;
	Vector2D _vDrawSize;

public:
	bool Frame() override;
	void SetRect(const Rect& rt);
	void SetPosition(const Vector2D& vPos);
	void SetDirection(const Vector2D& vDir);
	void UpdateVertexBuffer();
	void SetMask(Texture* pMaskTex);
};

class User2D : public Object2D
{
public:
	bool Frame() override;
};

class Npc2D : public Object2D
{
public:
	bool Frame() override;
};
class Sample : public GameCore
{
private:
	BaseObject* _pMap;
	std::vector<BaseObject*> _pNpcList;
	User2D* _pUser;
	std::vector<BaseObject*> _pObjectList;
	int _iTexIndex = 0;
public:
	virtual bool Init() final;
	virtual bool Frame() final;
	virtual bool Render() final;
	virtual bool Release() final;
};

