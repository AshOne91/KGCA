#include "Camera.h"
#include "Input.h"

void Camera::Update()
{
	_vRight.x = _matView._11;
	_vRight.y = _matView._21;
	_vRight.z = _matView._31;

	_vUp.x = _matView._12;
	_vUp.y = _matView._22;
	_vUp.z = _matView._32;

	_vLook.x = _matView._13;
	_vLook.y = _matView._23;
	_vLook.z = _matView._33;

	//_vRight.Normalized();
	//_vUp.Normalized();
	//_vLook.Normalized();
	D3DXVec3Normalize(&_vRight, &_vRight);
	D3DXVec3Normalize(&_vUp, &_vUp);
	D3DXVec3Normalize(&_vLook, &_vLook);
}
void Camera::CreateViewMatrix(TVector3 vEye, TVector3 vAt, TVector3 vUp)
{
	_vPos = vEye;
	_vTarget = vAt;
	_vUp = vUp;
	D3DXMatrixLookAtLH(&_matView, &vEye, &vAt, &vUp);
	//_matView.ViewLookAt(vEye, vAt, vUp);
	Update();
}
void Camera::CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio)
{
	_fNear = fNear;
	_fFar = fFar;
	_fFovY = fFovY;
	_fAspectRatio = fAspectRatio;
	D3DXMatrixPerspectiveFovLH(&_matProj, _fFovY, _fAspectRatio, _fNear, _fFar);
	//PerspectiveFovLH(_matProj, _fNear, _fFar, _fFovY, _fAspectRatio);
	//matProj.OrthoLH(800, 600, 0.0f, 100.0f);
	//OrthoOffCenterLH(matProj ,-400, 400, -300, 300, 0.0f, 100.0f);
}
bool Camera::Frame()
{
	if (I_Input.GetKey('W') == KEY_HOLD)
	{
		TVector3 v = _vLook * 10.0f * g_fSecondPerFrame;
		_vPos += v;
	}
	if (I_Input.GetKey('S') == KEY_HOLD)
	{
		TVector3 v = _vLook * -10.0f * g_fSecondPerFrame;
		_vPos += v;
	}
	if (I_Input.GetKey('A') == KEY_HOLD)
	{
		TVector3 v = _vRight * 10.0f * g_fSecondPerFrame;
		_vPos += v;
	}
	if (I_Input.GetKey('D') == KEY_HOLD)
	{
		TVector3 v = _vRight * -10.0f * g_fSecondPerFrame;
		_vPos += v;
	}
	if (I_Input.GetKey('Q') == KEY_HOLD)
	{
		TVector3 v = _vUp * 10.0f * g_fSecondPerFrame;
		_vPos += v;
	}
	if (I_Input.GetKey('E') == KEY_HOLD)
	{
		TVector3 v = _vUp * -10.0f * g_fSecondPerFrame;
		_vPos += v;
	}

	TVector3 vUp = { 0,1,0 };
	//TMatrix mCamera = TMath::RotationY(g_fGameTimer);
	//vPos = (vPos + vPosMovement) * mCamera;
	// 
	//_matView.ViewLookAt(_vPos, _vTarget, _vUp);
	D3DXMatrixLookAtLH(&_matView, &_vPos, &_vTarget, &_vUp);
	Update();
	return true;
}