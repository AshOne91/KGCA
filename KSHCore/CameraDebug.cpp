#include "CameraDebug.h"
#include "Input.h"
#include "TMath.h"

void CameraDebug::CreateViewMatrix(Vector3D vEye, Vector3D vAt, Vector3D vUp)
{
	_vPos = vEye;
	_vTarget = vAt;
	_vUp = vUp;
	_matView.ViewLookAt(vEye, vAt, vUp);
}

void CameraDebug::CreateProjMatrix(float fNear, float fFar, float fFovY, float fAspectRatio)
{
	_fNear = fNear;
	_fFar = fFar;
	_fFovY = fFovY;
	_fAspectRatio = fAspectRatio;
	PerspectiveFovLH(_matProj, _fNear, _fFar, _fFovY, _fAspectRatio);
	//matProj.OrthoLH(800, 600, 0.0f, 100.0f);
	//OrthoOffCenterLH(matProj ,-400, 400, -300, 300, 0.0f, 100.0f);
}

bool CameraDebug::Frame()
{
	//_fYaw, _fPitch, _fRoll
	if (I_Input.GetKey(VK_LBUTTON) == KEY_HOLD)
	{
		_fYaw += I_Input._ptOffset.x * 0.002f;
		_fPitch += I_Input._ptOffset.y * 0.002f;
	}
	if (I_Input.GetKey(VK_SPACE) == KEY_HOLD)
	{
		_fSpeed += g_fSecondPerFrame * 100.0f;
	}
	else
	{
		_fSpeed -= g_fSecondPerFrame * 100.0f;
	}
	_fSpeed = max(10.0f, _fSpeed);
	_fSpeed = min(100.0f, _fSpeed);

	if (I_Input.GetKey('W') == KEY_HOLD)
	{
		Vector3D v = _vLook * _fSpeed * g_fSecondPerFrame;
		_vPos += v;
	}
	if (I_Input.GetKey('S') == KEY_HOLD)
	{
		Vector3D v = _vLook * -_fSpeed * g_fSecondPerFrame;
		_vPos += v;
	}
	if (I_Input.GetKey('A') == KEY_HOLD)
	{
		Vector3D v = _vRight * -_fSpeed * g_fSecondPerFrame;
		_vPos += v;
	}
	if (I_Input.GetKey('D') == KEY_HOLD)
	{
		Vector3D v = _vRight * _fSpeed * g_fSecondPerFrame;
		_vPos += v;
	}
	if (I_Input.GetKey('Q') == KEY_HOLD)
	{
		Vector3D v = _vUp * _fSpeed * g_fSecondPerFrame;
		_vPos += v;
	}
	if (I_Input.GetKey('E') == KEY_HOLD)
	{
		Vector3D v = _vUp * -_fSpeed * g_fSecondPerFrame;
		_vPos += v;
	}


	TBASIS_EX::TVector3 vPos;
	vPos.x = _vPos.x;
	vPos.y = _vPos.y;
	vPos.z = _vPos.z;

	//////////////////////////// DebugCamera ////////////////////////////
	TBASIS_EX::TMatrix matWorld;
	TBASIS_EX::TMatrix matView;
	TBASIS_EX::TMatrix matRotation;
	TBASIS_EX::TQuaternion m_qRotation;
	TBASIS_EX::D3DXQuaternionRotationYawPitchRoll(&m_qRotation, _fYaw, _fPitch, _fRoll);
	TBASIS_EX::D3DXMatrixAffineTransformation(&matWorld, 1.0f, NULL, &m_qRotation, &vPos);
	TBASIS_EX::D3DXMatrixInverse(&matView, NULL, &matWorld);
	_matView = *((Matrix*)&matView);

	//////////////////////////// Model View////////////////////////////
	/*TVector vLocalUp = { 0.0f, 1.0f, 0.0f };
	TVector vLocalLook = { 0.0f, 0.0f, 1.0f };

	TBASIS_EX::TMatrix matRotation;
	TBASIS_EX::D3DXMatrixRotationYawPitchRoll(
		&matRotation, m_fYaw, 0, m_fRoll);
	TMatrix* matR = (TMatrix*)&matRotation;

	TVector vWorldLook = vLocalLook * (*matR);
	TVector vWorldUp = vLocalUp * (*matR);
	TVector vWorld = vWorldLook * 10.0f;
	m_vPos = m_vTarget - vWorld;
	m_matView.ViewLookAt(m_vPos, m_vTarget, m_vUp);*/

	Update();
	return true;
}

void CameraDebug::Update()
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

	_vRight.Normalized();
	_vUp.Normalized();
	_vLook.Normalized();

	_vFrustum.CreateFrustum(&_matView, &_matProj);
}
