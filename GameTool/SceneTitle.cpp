#include "pch.h"
#include "SceneTitle.h"
#include "Input.h"
#include "DxState.h"

bool SceneTitle::Init()
{
	I_Sprite.Load(L"SpriteInfo.txt");
	I_Sprite.Load(L"ui.txt");
	std::wstring shaderfilename = L"../../data/shader/DefaultShape.txt";
	_pBG = new BaseObject;
	_pBG->Create(_pd3dDevice, _pImmediateContext, shaderfilename, L"../../data/gameHeight.png");

	_pMap = new Map;
	// 2ÀÇ n½Â + 1
	_pMap->LoadHeightMap(_pd3dDevice, _pImmediateContext, L"../../data/map/heightMap513.bmp");
	//_pMap->Build(256 + 1, 256 + 1);
	_pMap->Build(_pMap->_iNumCols, _pMap->_iNumRows);
	_pMap->Create(_pd3dDevice, _pImmediateContext, L"DefaultObject.txt", L"../../data/map/Tile50.jpg");

	
	_pUser = new KUser;
	_pUser->Create(_pd3dDevice, _pImmediateContext, L"DefaultObject.txt", L"../../data/object/20200428_185613.jpg");
	D3DXMatrixTranslation(&_pUser->_matWorld,
		0,
		_pMap->GetHeight(0, 0),
		0);
	_pUser->_vPos.x = _pUser->_matWorld._41;
	_pUser->_vPos.y = _pUser->_matWorld._42;
	_pUser->_vPos.z = _pUser->_matWorld._43;

	_pMainCamera = new Camera;
	TVector3 vCamera = _pUser->_vPos + TVector3(0, 10, -10);
	vCamera.y = _pMap->GetHeight(vCamera.x, vCamera.z);
	_pMainCamera->CreateViewMatrix(vCamera, _pUser->_vPos, TVector3(0, 1, 0));
	_pMainCamera->CreateProjMatrix(1.0f, 1000.0f, PI * 0.25f,
		(float)g_rtClient.right / (float)g_rtClient.bottom);
	vBeforePos = _pUser->_vPos;
	return true;
}
bool SceneTitle::Frame()
{
	// _fYaw, _fPitch, _fRoll
	//if (I_Input.GetKey(VK_LBUTTON) == KEY_HOLD)
	//{
	//	_pMainCamera->_fYaw += I_Input._ptOffset.x * 0.002f;
	//	_pMainCamera->_fPitch += I_Input._ptOffset.y * 0.002f;
	//}

	TVector3 x = _pMainCamera->_vLook;
	x.y = 0;
	D3DXVec3Normalize(&x, &x);
	_pUser->_vLook = x;
	_pUser->_vPos.y = _pMap->GetHeight(_pUser->_vPos.x, _pUser->_vPos.z);
	_pUser->Frame();

	_pMainCamera->_vTarget = _pUser->_vPos;
	TVector3 vOffset = _pUser->_vPos - vBeforePos;
	_pMainCamera->_vPos += vOffset;
	_pMainCamera->_vPos.y = _pMap->GetHeight(_pMainCamera->_vPos.x, _pMainCamera->_vPos.z);
	_pMainCamera->_vPos.y = max(_pUser->_vPos.y, _pMainCamera->_vPos.y) + 10.0f;
	_pMainCamera->Frame();

	TVector3 r = _pMainCamera->_vRight;
	r.y = 0;
	D3DXVec3Normalize(&r, &r);

	if (I_Input.GetKey('A') == KEY_HOLD)
	{
		TVector3 v = -r * g_fSecondPerFrame * 10.0f;
		_pMainCamera->_vPos += v;
	}
	if (I_Input.GetKey('D') == KEY_HOLD)
	{
		TVector3 v = r * g_fSecondPerFrame * 10.0f;
		_pMainCamera->_vPos += v;
	}

	vBeforePos = _pUser->_vPos;
	//_pMainCamera->Frame();
	//_pBoxObjA->Frame();
	///*_pBoxObjA->_matWorld.RotationY(g_fGameTimer);
	//_pBoxObjA->_matWorld._41 = _pBoxObjA->_vPos.x;
	//_pBoxObjA->_matWorld._42 = _pBoxObjA->_vPos.y;
	//_pBoxObjA->_matWorld._43 = _pBoxObjA->_vPos.z;*/
	//_pBoxObjB->Frame();
	return true;
}
bool SceneTitle::Render()
{
	CameraDebug* pDCam = (CameraDebug*)_pMainCamera;
	_pUser->SetMatrix(nullptr, &_pMainCamera->_matView, &_pMainCamera->_matProj);
	_pUser->Render();
	//_pImmediateContext->OMSetDepthStencilState(DxState::g_pDefaultDepthStencil,
	//0xff);
	//_pMap->SetMatrix(nullptr, &_pMainCamera->_matView, &_pMainCamera->_matProj);
	//_pMap->UpdateBuffer((CameraDebug*)_pMainCamera);
	//_pMap->Render();

	//CameraDebug* pDCam = (CameraDebug*)_pMainCamera;
	//bool bRender = pDCam->_vFrustum.ClassifyPoint(_pBoxObjA->_vPos);
	//if (bRender)
	//{
	//	_pBoxObjA->SetMatrix(nullptr, &_pMainCamera->_matView, &_pMainCamera->_matProj);
	//	_pBoxObjA->Render();
	//}

	/*m_pImmediateContext->OMSetDepthStencilState(TDxState::g_pGreaterDepthStencil,
	0xff);*/
	//bRender = pDCam->_vFrustum.ClassifyPoint(_pBoxObjB->_vPos);
	//if (bRender)
	//{
	//	_pBoxObjB->SetMatrix(nullptr, &_pMainCamera->_matView, &_pMainCamera->_matProj);
	//	_pBoxObjB->Render();
	//}
	//m_pBG->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	//m_pBG->Render();

	return true;
}
bool SceneTitle::Release()
{
	_pBG->Release();
	delete _pBG;

	_pUser->Release();
	delete _pUser;

	//_pBoxObjA->Release();
	//delete _pBoxObjA;

	//_pBoxObjB->Release();
	//delete _pBoxObjB;

	_pMap->Release();
	delete _pMap;
	return true;
}

bool SceneTitle::IsNextScene()
{
	return false;
}
