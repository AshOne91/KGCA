#include "Sample.h"

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

bool Sample::Init()
{
	/*if (_FBXLoader.Init())
	{
		_FBXLoader.Load("../../data/fbx/box.fbx");
	}*/
	/*FbxLoader* pFbxLoaderC = new FbxLoader;
	if (pFbxLoaderC->Init())
	{
		pFbxLoaderC->Load("../../data/fbx/MultiCameras.fbx");
	}
	_fbxList.push_back(pFbxLoaderC);*/

	/*KFbxFile* pFbxLoaderA = new KFbxFile;
	if (pFbxLoaderA->Init())
	{
		if (pFbxLoaderA->Load("../../data/fbx/Turret_Deploy1/Turret_Deploy1.fbx"))
		{
			pFbxLoaderA->CreateConstantBuffer(_pd3dDevice.Get());
		}
	}
	_fbxList.push_back(pFbxLoaderA);*/

	/*FbxLoader* pFbxLoaderB = new FbxLoader;
	if (pFbxLoaderB->Init())
	{
		pFbxLoaderB->Load("../../data/fbx/sm_rock.fbx");
	}
	//_fbxList.push_back(pFbxLoaderB);*/

	KFbxFile* pFbxLoaderD = new KFbxFile;
	if (pFbxLoaderD->Init())
	{
		if (pFbxLoaderD->Load("../../data/fbx/Man.FBX"))
		{
			pFbxLoaderD->CreateConstantBuffer(_pd3dDevice.Get());
		}
	}
	_fbxList.push_back(pFbxLoaderD);

	W_STR szDefaultDir = L"../../data/fbx/";
	std::wstring shaderfilename = L"Skinning.txt";

	for (auto fbx : _fbxList)
	{
		for (int iObj = 0; iObj < fbx->_pDrawObjList.size(); ++iObj)
		{
			KFbxObject* pObj = fbx->_pDrawObjList[iObj];
			std::wstring szLoad = szDefaultDir + pObj->_szTextureName;
			pObj->Create(_pd3dDevice.Get(), _pImmediateContext.Get(), shaderfilename, szLoad);
		}
	}

	_pMainCamera = new CameraDebug;
	_pMainCamera->CreateViewMatrix(TVector3(0, 6, -10), TVector3(0, 0, 0), TVector3(0, 1, 0));
	_pMainCamera->CreateProjMatrix(1.0f, 10000.0f, PI * 0.25f, 
		(float)g_rtClient.right / (float)g_rtClient.bottom);
	return true;
}

bool Sample::Frame()
{
	ClearD3D11DeviceContext(_pImmediateContext.Get());
	//_FBXLoader.Frame();
	_pMainCamera->Frame();
	for (auto fbxfile : _fbxList)
	{
		fbxfile->UpdateFrame(_pImmediateContext.Get());
	}
	return true;
}

bool Sample::Render()
{
	if (I_Input.GetKey('V') == KEY_HOLD)
	{
		_pImmediateContext->RSSetState(DxState::g_pDefaultRSWireFrame);
	}

	TVector3 vLight(0, 0, 1);
	TMatrix matRotation;
	//matRotation.RotationY(g_fGameTimer);
	D3DXMatrixRotationY(&matRotation, g_fGameTimer);
	//vLight = vLight * matRotation;
	D3DXVec3TransformCoord(&vLight, &vLight, &matRotation);
	//vLight.Normalized();
	D3DXVec3Normalize(&vLight, &vLight);
	for (int iFbxFile = 0; iFbxFile < _fbxList.size(); ++iFbxFile)
	{
		_pImmediateContext->VSSetConstantBuffers(1, 1, &_fbxList[iFbxFile]->_pAnimBoneCB);
		for (int iObj = 0; iObj < _fbxList[iFbxFile]->_pDrawObjList.size(); ++iObj)
		{
			FbxObjectSkinning* pObj = _fbxList[iFbxFile]->_pDrawObjList[iObj];
			TMatrix matControlWorld;
			//D3DXMatrixRotationY(&matControlWorld, g_fGameTimer);
			pObj->_cbData.x = vLight.x;
			pObj->_cbData.y = vLight.y;
			pObj->_cbData.z = vLight.z;
			pObj->SetMatrix(&matControlWorld, &_pMainCamera->_matView, &_pMainCamera->_matProj);
			pObj->Render();
		}
	}

	_pImmediateContext->RSSetState(DxState::g_pDefaultRSSolid);
	return true;
}

bool Sample::Release()
{
	//_FBXLoader.Release();
	delete _pMainCamera;
	for (auto fbx : _fbxList)
	{
		fbx->Release();
		delete fbx;
	}
	return true;
}

GAME_RUN(FBXLoader, 800, 600)