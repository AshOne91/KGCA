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
	_pMap->Build(512 + 1, 512 + 1);
	_pMap->Create(_pd3dDevice, _pImmediateContext, L"DefaultObject.txt", L"../../data/map/Tile50.jpg");

	_pBoxObjA = new ObjectBox;
	_pBoxObjA->Create(_pd3dDevice, _pImmediateContext, L"DefaultObject.txt", L"../../data/object/20200428_185613.jpg");
	_pBoxObjA->_matWorld.Translation(0, 0, 2);

	_pBoxObjB = new ObjectBox;
	_pBoxObjB->Create(_pd3dDevice, _pImmediateContext, L"DefaultObject.txt", L"../../data/_RAINBOW.bmp");
	_pBoxObjB->_matWorld.Translation(1, 0, 4);

	_pMainCamera = new CameraDebug;
	_pMainCamera->CreateViewMatrix(Vector3D(0, 0, -10), Vector3D(0, 0, 0), Vector3D(0, 1, 0));
	_pMainCamera->CreateProjMatrix(1.0f, 10000.0f, PI * 0.25f,
		(float)g_rtClient.right / (float)g_rtClient.bottom);

	return true;
}
bool SceneTitle::Frame()
{
	// _fYaw, _fPitch, _fRoll
	if (I_Input.GetKey(VK_LBUTTON) == KEY_HOLD)
	{
		_pMainCamera->_fYaw += I_Input._ptOffset.x * 0.002f;
		_pMainCamera->_fPitch += I_Input._ptOffset.y * 0.002f;
	}
	_pMainCamera->Frame();
	_pBoxObjA->Frame();
	_pBoxObjA->_matWorld.RotationY(g_fGameTimer);
	_pBoxObjA->_matWorld._41 = _pBoxObjA->_vPos.x;
	_pBoxObjA->_matWorld._42 = _pBoxObjA->_vPos.y;
	_pBoxObjA->_matWorld._43 = _pBoxObjA->_vPos.z;
	_pBoxObjB->Frame();
	return true;
}
bool SceneTitle::Render()
{
	_pImmediateContext->OMSetDepthStencilState(DxState::g_pDefaultDepthStencil,
	0xff);
	_pMap->SetMatrix(nullptr, &_pMainCamera->_matView, &_pMainCamera->_matProj);
	_pMap->Render();

	_pBoxObjA->SetMatrix(nullptr, &_pMainCamera->_matView, &_pMainCamera->_matProj);
	_pBoxObjA->Render();
	/*m_pImmediateContext->OMSetDepthStencilState(TDxState::g_pGreaterDepthStencil,
	0xff);*/
	_pBoxObjB->SetMatrix(nullptr, &_pMainCamera->_matView, &_pMainCamera->_matProj);
	_pBoxObjB->Render();
	//m_pBG->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	//m_pBG->Render();
	return true;
}
bool SceneTitle::Release()
{
	_pBG->Release();
	delete _pBG;

	_pBoxObjA->Release();
	delete _pBoxObjA;

	_pBoxObjB->Release();
	delete _pBoxObjB;

	_pMap->Release();
	delete _pMap;
	return true;
}

bool SceneTitle::IsNextScene()
{
	return false;
}
