#pragma once
#include "Camera.h"

class CameraDebug : public Camera
{
public:
	virtual void CreateViewMatrix(Vector3D vEye, Vector3D vAt, Vector3D vUp);
	virtual void CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio);
	virtual bool Frame();
};

