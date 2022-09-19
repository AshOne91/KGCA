#pragma once
#include "GameCore.h"
#include "User2D.h"
#include "MapObject.h"

typedef std::vector<RECT>  RECT_ARRAY;
class Sprite : public Object2D
{
	std::vector<Sprite*>  _pChild;
	Rect    _rtCollision;
public:
	// È­¸é ÁÂÇ¥ -> NDC ÁÂÇ¥ 
	void  SetPosition(Vector2D vPos)
	{
		_vPos = vPos;
		Vector2D	vDrawSize;
		vDrawSize.x = _rtInit.w / 2.0f;
		vDrawSize.y = _rtInit.h / 2.0f;
		_rtCollision.Set(
			vPos.x - vDrawSize.x,
			vPos.y - vDrawSize.y,
			_rtInit.w,
			_rtInit.h);
		// 0  ~ 800   -> 0~1 ->  -1 ~ +1
		_vDrawPos.x = (_rtCollision.x1 / g_rtClient.right) * 2.0f - 1.0f;
		_vDrawPos.y = -((_rtCollision.y1 / g_rtClient.bottom) * 2.0f - 1.0f);
		_vDrawSize.x = (_rtInit.w / g_rtClient.right) * 2;
		_vDrawSize.y = (_rtInit.h / g_rtClient.bottom) * 2;
		UpdateVertexBuffer();
	}
};
class Sample : public GameCore
{
	Vector2D		_vCamera;
	MapObject* _pMap;
	User2D* _pUser;
	Sprite* _pObject;
	std::vector<RECT_ARRAY> _rtSpriteList;
	std::vector<Sprite*> _pSpriteList;
public:
	bool GameDataLoad(const TCHAR* pszLoad);
	virtual bool		Init() override;
	virtual bool		Frame() override;
	virtual bool		Render() override;
	virtual bool		Release() override;
};
