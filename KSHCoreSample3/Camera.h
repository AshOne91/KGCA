#pragma once
#include "BaseObject.h"

class Camera : public BaseObject
{
public:
	Vector3D _vCameraPos;
	Vector3D _vTarget = { 0, 0, 0 };
	Vector3D _vUp = { 0,1,0 };
	float _fNear;
	float _fFar;
	float _fFovY;
	float _fAspectRatio;

public:
	virtual void CreateViewMatrix(Vector3D vEye, Vector3D vAt, Vector3D vUp);
	virtual void CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio);
	virtual bool Frame();

};

