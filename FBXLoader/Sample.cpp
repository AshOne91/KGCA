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

	FbxLoader* pFbxLoaderA = new FbxLoader;
	if (pFbxLoaderA->Init())
	{
		pFbxLoaderA->Load("../../data/fbx/Turret_Deploy1/Turret_Deploy1.fbx");
	}
	_fbxList.push_back(pFbxLoaderA);

	/*FbxLoader* pFbxLoaderB = new FbxLoader;
	if (pFbxLoaderB->Init())
	{
		pFbxLoaderB->Load("../../data/fbx/sm_rock.fbx");
	}
	//_fbxList.push_back(pFbxLoaderB);*/

	W_STR szDefaultDir = L"../../data/fbx/";
	std::wstring shaderfilename = L"../../data/shader/DefaultObject.txt";

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
	_pMainCamera->CreateViewMatrix(TVector3(0, 6, -50), TVector3(0, 0, 0), TVector3(0, 1, 0));
	_pMainCamera->CreateProjMatrix(1.0f, 10000.0f, PI * 0.25f, 
		(float)g_rtClient.right / (float)g_rtClient.bottom);
	return true;
}

bool Sample::Frame()
{
	ClearD3D11DeviceContext(_pImmediateContext.Get());
	//_FBXLoader.Frame();
	_pMainCamera->Frame();
	for (auto fbx : _fbxList)
	{
		fbx->Frame();
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
	for (int iModel = 0; iModel < _fbxList.size(); ++iModel)
	{
		for (int iObj = 0; iObj < _fbxList[iModel]->_pDrawObjList.size(); ++iObj)
		{
			KFbxObject* pObj = _fbxList[iModel]->_pDrawObjList[iObj];
			//Matrix matWorld;
			//matWorld._41 = 100 * iModel;
			pObj->_fAnimFrame = pObj->_fAnimFrame +
				g_fSecondPerFrame * pObj->_fAnimSpeed *
				pObj->_AnimScene.fFrameSpeed * pObj->_fAnimInverse;
			if (pObj->_fAnimFrame > pObj->_AnimScene.iEndFrame ||
				pObj->_fAnimFrame < pObj->_AnimScene.iStartFrame)
			{
				pObj->_fAnimFrame = min(pObj->_fAnimFrame, pObj->_AnimScene.iEndFrame);
				pObj->_fAnimFrame = max(pObj->_fAnimFrame, pObj->_AnimScene.iStartFrame);
				pObj->_fAnimInverse *= -1.0f;
			}

			TMatrix matWorld = pObj->_AnimTracks[pObj->_fAnimFrame].matAnim;
			pObj->_cbData.x = vLight.x;
			pObj->_cbData.y = vLight.y;
			pObj->_cbData.z = vLight.z;
			pObj->SetMatrix(&matWorld,
				&_pMainCamera->_matView,
				&_pMainCamera->_matProj);
			pObj->Render();
		}
	}

	_pImmediateContext->RSSetState(DxState::g_pDefaultRSSolid);
	return true;
}

bool Sample::Release()
{
	//_FBXLoader.Release();
	for (auto fbx : _fbxList)
	{
		fbx->Release();
	}
	return true;
}

GAME_RUN(FBXLoader, 800, 600)