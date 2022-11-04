#pragma once
#include "BaseObject.h"
#include "Frustum.h"

class Camera : public BaseObject
{
public:
	TVector3   _vPos;
	TVector3   _vLook;//z axis
	TVector3   _vUp = { 0,1,0 };;// y
	TVector3   _vRight; //z
	float     _fYaw = 0.0f;
	float     _fPitch = 0.0f;
	float     _fRoll = 0.0f;
	float     _fDistance = 0.0f;
	float     _fSpeed = 10.0f;
public:
	Frustum _vFrustum;
public:
	TVector3			_vTarget = { 0,0,0 };
	float			_fNear;
	float			_fFar;
	float			_fFovY;
	float			_fAspectRatio;
public:
	virtual void  CreateViewMatrix(TVector3 vEye, TVector3 vAt, TVector3 vUp);
	virtual void  CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio);
	virtual bool  Frame();
	virtual void Update();
};

