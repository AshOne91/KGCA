#pragma once
#include "BaseObject.h"

class Camera : public BaseObject
{
public:
	Vector3D   _vPos;
	Vector3D   _vLook;//z axis
	Vector3D   _vUp = { 0,1,0 };;// y
	Vector3D   _vRight; //z
	float     _fYaw = 0.0f;
	float     _fPitch = 0.0f;
	float     _fRoll = 0.0f;
	float     _fDistance = 0.0f;
	float     _fSpeed = 10.0f;
public:
	Vector3D			_vTarget = { 0,0,0 };
	float			_fNear;
	float			_fFar;
	float			_fFovY;
	float			_fAspectRatio;
public:
	virtual void  CreateViewMatrix(Vector3D vEye, Vector3D vAt, Vector3D vUp);
	virtual void  CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio);
	virtual bool  Frame();
	void Update();
};

