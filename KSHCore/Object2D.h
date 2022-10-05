#pragma once
#include "BaseObject.h"
#include "Collision.h"

class Object2D : public BaseObject
{
public:
	W_STR _szName;
	UINT _iIndex;
	W_STR _szTexturePath;
	W_STR _szMaskTexturePath;
	W_STR _szShaderPath;

public:
	Texture* _pMaskTex = nullptr;
	POINT _ptImageSize;
	Rect _rtInit;
	Rect _rtUV;
	Vector2D _vPos;
	Vector2D _vDir;
	float _fSpeed = 100.0f;
	Vector2D _vNDCPos;
	Vector2D _vDrawSize;
	Vector2D _vBeforePos;
	Vector2D _vOffsetPos;
	bool _bAlpha = true;

public:
	Vector2D _vCameraPos;
	Vector2D _vViewSize;
	virtual void SetCameraPos(const Vector2D& vCamera);
	virtual void SetCameraSize(const Vector2D& vSize);
	virtual void ScreenToNDC();
	virtual void ScreenToCamera(const Vector2D& vCameraPos, const Vector2D& vViewPort);

public:
	bool Frame() override;
	virtual void SetRect(const Rect& rt);
	virtual void SetPosition(const Vector2D& vPos);
	virtual void SetPosition(const Vector2D& vPos, const Vector2D& vCamera);
	virtual void SetDirection(const Vector2D& vDir);
	virtual void UpdateVertexBuffer() override;
	virtual void UpdateVertexBufferFlip();
	virtual void SetMask(Texture* pMaskTex);
};
