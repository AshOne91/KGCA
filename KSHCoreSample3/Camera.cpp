#include "Camera.h"
#include "Input.h"

void Camera::CreateViewMatrix(Vector3D vEye, Vector3D vAt, Vector3D vUp)
{
	_vCameraPos = vEye;
	_vTarget = vAt;
	_vUp = vUp;
	_matView.ViewLookAt(vEye, vAt, vUp);
}

void Camera::CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio)
{
	_fNear = fNear;
	_fFar = fFar;
	_fFovY = fFovY;
	_fAspectRatio = fAspectRatio;
	PerspectiveFovLH(_matProj, 1.0f, 100.0f, 3.141592f * 0.5f, 800.0f / 600.0f);
}

bool Camera::Frame()
{
	if (I_Input.GetKey('W') == KEY_HOLD)
	{
		_vCameraPos.z += 10.0f * g_fSecondPerFrame;
	}
	if (I_Input.GetKey('S') == KEY_HOLD)
	{
		_vCameraPos.z -= 10.0f * g_fSecondPerFrame;
	}
	if (I_Input.GetKey('A') == KEY_HOLD)
	{
		_vCameraPos.x -= 10.0f * g_fSecondPerFrame;
	}
	if (I_Input.GetKey('D') == KEY_HOLD)
	{
		_vCameraPos.x += 10.0f * g_fSecondPerFrame;
	}
	if (I_Input.GetKey('Q') == KEY_HOLD)
	{
		_vCameraPos.y += 10.0f * g_fSecondPerFrame;
	}
	if (I_Input.GetKey('E') == KEY_HOLD)
	{
		_vCameraPos.y -= 10.0f * g_fSecondPerFrame;
	}

	Vector3D vUp = { 0,1,0 };
	//TMatrix mCamera = TMath::RotationY(g_fGameTimer);
	//vPos = (vPos + vPosMovement) * mCamera;
	_matView.ViewLookAt(_vCameraPos, _vTarget, _vUp);
	return true;
}
