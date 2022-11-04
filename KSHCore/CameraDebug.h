#pragma once
#include "Camera.h"

class CameraDebug : public Camera
{
public:
	virtual void CreateViewMatrix(TVector3 vEye, TVector3 vAt, TVector3 vUp);
	virtual void CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio);
	virtual bool Frame();
	virtual void Update() override;
};

