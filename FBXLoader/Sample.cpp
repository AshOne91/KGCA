#include "Sample.h"

bool Sample::Init()
{
	/*if (_FBXLoader.Init())
	{
		_FBXLoader.Load("../../data/fbx/box.fbx");
	}*/
	FbxLoader* pFbxLoaderC = new FbxLoader;
	if (pFbxLoaderC->Init())
	{
		pFbxLoaderC->Load("../../data/fbx/MultiCameras.fbx");
	}
	_fbxList.push_back(pFbxLoaderC);

	/*TFbxLoader* pFbxLoaderA = new TFbxLoader;
	if (pFbxLoaderA->Init())
	{
		pFbxLoaderA->Load("../../data/fbx/box.fbx");
	}
	m_fbxList.push_back(pFbxLoaderA);

	TFbxLoader* pFbxLoaderB = new TFbxLoader;
	if (pFbxLoaderB->Init())
	{
		pFbxLoaderB->Load("../../data/fbx/sm_rock.fbx");
	}
	m_fbxList.push_back(pFbxLoaderB);*/

	W_STR szDefaultDir = L"../../data/fbx/";
	std::wstring shaderfilename = L"../../data/shader/DefaultObject.txt";

	for (auto fbx : _fbxList)
	{
		for (int iObj = 0; iObj < fbx->_pDrawObjList.size(); ++iObj)
		{
			KFbxObject* pObj = fbx->_pDrawObjList[iObj];
			std::wstring szLoad = szDefaultDir + pObj->_szTextureName;
			if (pObj->vbDataList.size() == 0)
			{
				pObj->Create(_pd3dDevice.Get(), _pImmediateContext.Get(), shaderfilename, szLoad);
			}
			else
			{
				for (int iSubObj = 0; iSubObj < pObj->vbDataList.size(); ++iSubObj)
				{
					KFbxObject* pSubObj = new KFbxObject;
					std::wstring szSubLoad = szDefaultDir + pObj->vbTexList[iSubObj];
					if (pObj->vbDataList[iSubObj].size() != 0)
					{
						pSubObj->_VertexList = pObj->vbDataList[iSubObj];
						pSubObj->Create(_pd3dDevice.Get(), _pImmediateContext.Get(), shaderfilename, szSubLoad);
						pObj->_pDrawChild.push_back(pSubObj);
					}
				}
			}
		}
	}

	_pMainCamera = new CameraDebug;
	_pMainCamera->CreateViewMatrix(Vector3D(50, 6, -50), Vector3D(0, 6, 0), Vector3D(0, 1, 0));
	_pMainCamera->CreateProjMatrix(1.0f, 1000.0f, PI * 0.25f, (float)g_rtClient.right / (float)g_rtClient.bottom);
	return true;
}

bool Sample::Frame()
{
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
	for (int iModel = 0; iModel < _fbxList.size(); ++iModel)
	{
		for (int iObj = 0; iObj < _fbxList[iModel]->_pDrawObjList.size(); ++iObj)
		{
			KFbxObject* pObj = _fbxList[iModel]->_pDrawObjList[iObj];
			if (pObj->_pDrawChild.size() == 0)
			{
				Matrix matWorld;
				matWorld._41 = 100 * iModel;
				pObj->SetMatrix(nullptr,
					&_pMainCamera->_matView,
					&_pMainCamera->_matProj);
				pObj->Render();
			}
			else
			{
				for (int iSubObj = 0; iSubObj < pObj->_pDrawChild.size(); ++iSubObj)
				{
					KFbxObject* pSubObj = pObj->_pDrawChild[iSubObj];
					Matrix matWorld;
					matWorld._41 = 100 * iModel;
					pSubObj->SetMatrix(&matWorld,
						&_pMainCamera->_matView,
						&_pMainCamera->_matProj);
					pSubObj->Render();
				}
			}
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