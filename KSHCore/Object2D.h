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
	TVector2 _vPos;
	TVector2 _vDir;
	float _fSpeed = 100.0f;
	TVector2 _vNDCPos;
	TVector2 _vDrawSize;
	TVector2 _vBeforePos;
	TVector2 _vOffsetPos;
	bool _bAlpha = true;

public:
	TVector2 _vCameraPos;
	TVector2 _vViewSize;
	virtual void SetCameraPos(const TVector2& vCamera);
	virtual void SetCameraSize(const TVector2& vSize);
	virtual void ScreenToNDC();
	virtual void ScreenToCamera(const TVector2& vCameraPos, const TVector2& vViewPort);

public:
	bool Frame() override;
	virtual void SetRect(const Rect& rt);
	virtual void SetPosition(const TVector2& vPos);
	virtual void SetPosition(const TVector2& vPos, const TVector2& vCamera);
	virtual void SetDirection(const TVector2& vDir);
	virtual void UpdateVertexBuffer() override;
	virtual void UpdateVertexBufferFlip();
	virtual void SetMask(Texture* pMaskTex);
};
