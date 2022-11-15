#include "pch.h"
#include "Sample.h"

bool Sample::Init()
{
	_pTitle = std::make_shared<SceneTitle>();
	_pInGame = std::make_shared<SceneInGame>();
	_pTitle->Create(_pd3dDevice.Get(), _pImmediateContext.Get(), L"");
	_pInGame->Create(_pd3dDevice.Get(), _pImmediateContext.Get(), L"");
	_pTitle->Init();
	_pInGame->Init();
	_pCurrentScene = _pTitle;

	_Quadtree.Create(
		((SceneTitle*)_pCurrentScene.get())->_pMainCamera,
		((SceneTitle*)_pCurrentScene.get())->_pMap);

	std::wstring shaderfilename = L"DefaultShape.txt";
	_DirLine.Create(_pd3dDevice.Get(), _pImmediateContext.Get(), shaderfilename,
		L"../../data/gameHeight.png");

	KFbxFile* pFbxLoaderD = new KFbxFile;
	if (pFbxLoaderD->Init())
	{
		if (pFbxLoaderD->Load("../../data/fbx/Man.FBX"))
		{
			pFbxLoaderD->CreateConstantBuffer(_pd3dDevice.Get());
		}
	}
	_fbxList.push_back(pFbxLoaderD);

	KFbxFile* pFbxLoaderA = new KFbxFile;
	if (pFbxLoaderA->Init())
	{
		if (pFbxLoaderA->Load("../../data/fbx/Swat@turning_right_45_degrees.fbx"))
		{
			pFbxLoaderA->CreateConstantBuffer(_pd3dDevice.Get());
		}
	}
	_fbxList.push_back(pFbxLoaderA);

	KFbxFile* pFbxLoaderB = new KFbxFile;
	if (pFbxLoaderB->Init())
	{
		pFbxLoaderB->Load("../../data/fbx/Swat.fbx");
	}
	_fbxList.push_back(pFbxLoaderB);

	W_STR szDefaultDir = L"../../data/fbx/";
	std::wstring fbxShaderfilename = L"Skinning.txt";

	for (auto fbx : _fbxList)
	{
		for (int iObj = 0; iObj < fbx->_pDrawObjList.size(); iObj++)
		{
			KFbxObject* pObj = fbx->_pDrawObjList[iObj];
			std::wstring  szLoad = szDefaultDir + pObj->_szTextureName;
			pObj->Create(_pd3dDevice.Get(), _pImmediateContext.Get(), fbxShaderfilename, szLoad);
		}
	}

	_UserCharacter = new Character;
	_UserCharacter->_iFbxListID = 2;
	_UserCharacter->_pFbxFile = _fbxList[_UserCharacter->_iFbxListID];
	_UserCharacter->_pAnionFbxFile = pFbxLoaderA;
	if (_UserCharacter->_pAnionFbxFile)
	{
		_UserCharacter->_AnimScene = _UserCharacter->_pAnionFbxFile->_AnimScene;
		_UserCharacter->_ActionFileList.insert(std::make_pair(L"walking", pFbxLoaderA));
		_UserCharacter->_ActionCurrent.iStartFrame = pFbxLoaderA->_AnimScene.iStartFrame;
		_UserCharacter->_ActionCurrent.iEndFrame = 50;// pFbxLoaderA->m_AnimScene.iEndFrame;
	}
	else
	{
		_UserCharacter->_AnimScene = _UserCharacter->_pFbxFile->_AnimScene;
		ActionTable action;
		action.iStartFrame = _UserCharacter->_AnimScene.iStartFrame;
		action.iEndFrame = _UserCharacter->_AnimScene.iEndFrame;
		action.bLoop = true;
		_UserCharacter->_ActionList.insert(std::make_pair(L"idle", action));
	}

	/*action.iStartFrame = 61;
	action.iEndFrame = 91;
	action.bLoop = true;
	m_UserCharacter->m_ActionList.insert(std::make_pair(L"walk", action));
	action.iStartFrame = 92;
	action.iEndFrame = 116;
	action.bLoop = true;
	m_UserCharacter->m_ActionList.insert(std::make_pair(L"run", action));
	action.iStartFrame = 120;
	action.iEndFrame = 225;
	action.bLoop = false;
	m_UserCharacter->m_ActionList.insert(std::make_pair(L"jump", action));
	action.iStartFrame = 205;
	action.iEndFrame = 289;
	action.bLoop = false;
	m_UserCharacter->m_ActionList.insert(std::make_pair(L"attack", action));*/
	_UserCharacter->CreateConstantBuffer(_pd3dDevice.Get());

	for (int iObj = 0; iObj < 5; iObj++)
	{
		Character* pNpc = new Character;
		pNpc->_iFbxListID = 0;
		pNpc->_pFbxFile = _fbxList[pNpc->_iFbxListID];
		pNpc->_matWorld._41 = -4.0f + iObj * 2;
		pNpc->_AnimScene = pNpc->_pFbxFile->_AnimScene;
		pNpc->CreateConstantBuffer(_pd3dDevice.Get());
		ActionTable action;
		action.iStartFrame = 61;
		action.iEndFrame = 91;
		action.bLoop = true;
		pNpc->_ActionList.insert(std::make_pair(L"walk", action));
		pNpc->_ActionCurrent = pNpc->_ActionList.find(L"walk")->second;

		_NpcList.push_back(pNpc);
	}

	D3DXMatrixScaling(&_DirLine._matWorld, 1000.0f, 1000.0f, 1000.0f);
	return true;
}
bool Sample::Frame()
{
	ClearD3D11DeviceContext(_pImmediateContext.Get());
	if (_pCurrentScene->IsNextScene())
	{
		_pCurrentScene = _pInGame;
	}
	_pCurrentScene->Frame();

	for (auto npc : _NpcList)
	{
		npc->UpdateFrame(_pImmediateContext.Get());
	}
	/*if (I_Input.GetKey('J') == KEY_HOLD)
	{
		TActionTable action = m_UserCharacter->m_ActionList.find(L"jump")->second;
		m_UserCharacter->m_ActionCurrent = action;
	}
	else
	{
		TActionTable action = m_UserCharacter->m_ActionList.find(L"idle")->second;
		m_UserCharacter->m_ActionCurrent = action;
	}*/
	_UserCharacter->UpdateFrame(_pImmediateContext.Get());
	return true;
}
bool Sample::Render()
{
	if (I_Input.GetKey('V') == KEY_HOLD)
	{
		_pImmediateContext->RSSetState(DxState::g_pDefaultRSWireFrame);
	}
	SceneTitle* pScene = (SceneTitle*)_pCurrentScene.get();

	TVector3 vLight(0, 0, 1);
	TMatrix matRotation;
	D3DXMatrixRotationY(&matRotation, g_fGameTimer);
	//vLight = vLight * matRotation;
	D3DXVec3TransformCoord(&vLight, &vLight, &matRotation);
	D3DXVec3Normalize(&vLight, &vLight);

	TMatrix matWorld;
	matWorld._41 = pScene->_pUser->_vPos.x;
	matWorld._42 = pScene->_pUser->_vPos.y;
	matWorld._43 = pScene->_pUser->_vPos.z;

	for (int iNpc = 0; iNpc < _NpcList.size(); iNpc++)
	{
		matWorld._41 += iNpc * 10.0f;
		_NpcList[iNpc]->SetMatrix(&matWorld, &pScene->_pMainCamera->_matView, &pScene->_pMainCamera->_matProj);
		_NpcList[iNpc]->Render(_pImmediateContext.Get());
	}
	matWorld._41 = pScene->_pUser->_vPos.x;
	matWorld._42 = pScene->_pUser->_vPos.y;
	matWorld._43 = pScene->_pUser->_vPos.z;
	_UserCharacter->SetMatrix(&matWorld, &pScene->_pMainCamera->_matView, &pScene->_pMainCamera->_matProj);
	_UserCharacter->Render(_pImmediateContext.Get());
	_pImmediateContext->RSSetState(DxState::g_pDefaultRSSolid);

	_pImmediateContext->OMSetDepthStencilState(DxState::g_pDefaultDepthStencil, 0xff);

	pScene->_pMap->SetMatrix(nullptr,
		&pScene->_pMainCamera->_matView,
		&pScene->_pMainCamera->_matProj);
	_Quadtree.Frame();
	_Quadtree.Render();

	_pCurrentScene->Render();
	_DirLine.SetMatrix(nullptr, &_pCurrentScene->_pMainCamera->_matView,
		&_pCurrentScene->_pMainCamera->_matProj);
	_DirLine.Render();
	return true;
}
bool Sample::Release()
{
	for (auto npc : _NpcList)
	{
		npc->Release();
		delete npc;
	}
	for (auto fbx : _fbxList)
	{
		fbx->Release();
		delete fbx;
	}
	_UserCharacter->Release();
	delete _UserCharacter;

	_DirLine.Release();
	_pTitle->Release();
	_pInGame->Release();
	return true;
}

HRESULT Sample::CreateDXResource()
{
	GameCore::CreateDXResource();
	if (_pCurrentScene)
	{
		_pCurrentScene->_pMainCamera->CreateProjMatrix(
			1.0f, 1000.0f, PI * 0.25f,
			(float)g_rtClient.right / (float)g_rtClient.bottom);
	}
	return S_OK;
}

void Sample::ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext)
{
	// Unbind all objects from the immediate context
	if (pd3dDeviceContext == NULL) return;

	ID3D11ShaderResourceView* pSRVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ID3D11RenderTargetView* pRTVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ID3D11DepthStencilView* pDSV = NULL;
	ID3D11Buffer* pBuffers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ID3D11SamplerState* pSamplers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	UINT StrideOffset[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	// Shaders
	//pd3dDeviceContext->VSSetShader(NULL, NULL, 0);
	//pd3dDeviceContext->HSSetShader(NULL, NULL, 0);
	//pd3dDeviceContext->DSSetShader(NULL, NULL, 0);
	//pd3dDeviceContext->GSSetShader(NULL, NULL, 0);
	//pd3dDeviceContext->PSSetShader(NULL, NULL, 0);

	//// IA clear
	//pd3dDeviceContext->IASetVertexBuffers(0, 16, pBuffers, StrideOffset, StrideOffset);
	//pd3dDeviceContext->IASetIndexBuffer(NULL, DXGI_FORMAT_R16_UINT, 0);
	//pd3dDeviceContext->IASetInputLayout(NULL);

	//// Constant buffers
	//pd3dDeviceContext->VSSetConstantBuffers(0, 14, pBuffers);
	//pd3dDeviceContext->HSSetConstantBuffers(0, 14, pBuffers);
	//pd3dDeviceContext->DSSetConstantBuffers(0, 14, pBuffers);
	//pd3dDeviceContext->GSSetConstantBuffers(0, 14, pBuffers);
	//pd3dDeviceContext->PSSetConstantBuffers(0, 14, pBuffers);

	// Resources
	pd3dDeviceContext->VSSetShaderResources(0, 16, pSRVs);
	//pd3dDeviceContext->HSSetShaderResources(0, 16, pSRVs);
	//pd3dDeviceContext->DSSetShaderResources(0, 16, pSRVs);
	//pd3dDeviceContext->GSSetShaderResources(0, 16, pSRVs);
	pd3dDeviceContext->PSSetShaderResources(0, 16, pSRVs);

	//// Samplers
	//pd3dDeviceContext->VSSetSamplers(0, 16, pSamplers);
	//pd3dDeviceContext->HSSetSamplers(0, 16, pSamplers);
	//pd3dDeviceContext->DSSetSamplers(0, 16, pSamplers);
	//pd3dDeviceContext->GSSetSamplers(0, 16, pSamplers);
	//pd3dDeviceContext->PSSetSamplers(0, 16, pSamplers);

	//// Render targets
	//pd3dDeviceContext->OMSetRenderTargets(8, pRTVs, pDSV);

	//// States
	//FLOAT blendFactor[4] = { 0,0,0,0 };
	//pd3dDeviceContext->OMSetBlendState(NULL, blendFactor, 0xFFFFFFFF);
	//pd3dDeviceContext->OMSetDepthStencilState(NULL, 0);
	//pd3dDeviceContext->RSSetState(NULL);
}
