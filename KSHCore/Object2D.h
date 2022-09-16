#pragma once
#include "BaseObject.h"
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
	Vector2D _vDrawPos;
	Vector2D _vDrawSize;

public:
	Vector2D _vCameraPos;
	Vector2D _vViewSize;
	void SetCameraPos(const Vector2D& vCamera);
	void SetCameraSize(const Vector2D& vSize);
	void ScreenToNDC();
	void ScreenToCamera(const Vector2D& vCameraPos, const Vector2D& vViewPort);

public:
	bool Frame() override;
	virtual void SetRect(const Rect& rt);
	virtual void SetPosition(const Vector2D& vPos);
	virtual void SetPosition(const Vector2D& vPos, const Vector2D& vCamera);
	virtual void SetDirection(const Vector2D& vDir);
	virtual void UpdateVertexBuffer() override;
	virtual void SetMask(Texture* pMaskTex);
};
