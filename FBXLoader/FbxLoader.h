#pragma once
#include "Std.h"
#include <fbxsdk.h>
#include "Object3D.h"
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "zlib-md.lib")

class KFbxObject : public Object3D
{
public:
	std::vector<ID3D11Buffer*> _pSubVB;
	std::vector<std::vector<PNCT_VERTEX>> vbDataList;
	std::vector<Texture*> _pSubTexture;
	std::vector<W_STR> vbTexList;

public:
	void CreateVertexData() {}
	HRESULT CreateVertexBuffer()
	{
		HRESULT hr = S_OK;
		if (vbDataList.size() > 0)
		{
			for (int ivb = 0; ivb < vbDataList.size(); ++ivb)
			{
				_pSubVB.push_back(
					KDX::CreateVertexBuffer(_pd3dDevice, &vbDataList[ivb].at(0), vbDataList[ivb].size(), sizeof(PNCT_VERTEX))
				);
			}
		}
		else
		{
			hr = Object3D::CreateVertexBuffer();
		}
		return S_OK;
	}
	HRESULT CreateIndexBuffer()
	{
		return S_OK;
	}
	bool LoadTexture(W_STR texturename)
	{
		if (vbTexList.size() > 0)
		{
			W_STR szDefaultDir = L"../../data/fbx/";
			_pSubTexture.resize(vbTexList.size());
			for (int ivb = 0; ivb < vbTexList.size(); ++ivb)
			{
				W_STR szLoadFile = szDefaultDir + vbTexList[ivb];
				_pSubTexture[ivb] = I_Tex.Load(szLoadFile);
			}
		}
		else
		{
			_pTexture = I_Tex.Load(texturename);
			if (_pTexture != nullptr)
			{
				_pTextureSRV = _pTexture->_pTextureSRV;
				return true;
			}
		}
		return false;
	}
	bool PostRender()
	{
		if (_pIndexBuffer == nullptr)
		{
			if (vbDataList.size() > 0)
			{
				for (int iSubObj = 0; iSubObj < _pSubVB.size(); ++iSubObj)
				{
					UINT stride = sizeof(PNCT_VERTEX); // 정점1개의 바이트 용량
					UINT offset = 0; // 정점버퍼에서 출발지점(바이트)
					//SLOT(레지스터리)
					_pImmediateContext->IASetVertexBuffers(0, 1, &_pSubVB[iSubObj], &stride, &offset);
					_pImmediateContext->PSSetShaderResources(0, 1, &_pSubTexture[iSubObj]->_pTextureSRV);
					_pImmediateContext->Draw(vbDataList[iSubObj].size(), 0);
				}
			}
			else
			{
				_pImmediateContext->Draw(_VertexList.size(), 0);
			}
		}
		else
		{
			_pImmediateContext->DrawIndexed(_dwFace * 3, 0, 0);
		}
		return true;
	}
	bool Release()
	{
		Object3D::Release();

		for (int iSubObj = 0; iSubObj < _pSubVB.size(); ++iSubObj)
		{
			if (_pSubVB[iSubObj])
			{
				_pSubVB[iSubObj]->Release();
			}
		}
		return true;
	}
};

class FbxLoader
{
public:
	FbxManager* _pFbxManager;
	FbxImporter* _pFbxImporter;
	FbxScene* _pFbxScene;
	FbxNode* _pRootNode;
	std::vector<FbxMesh*> _pFbxMeshList;
	std::vector<KFbxObject*> _pDrawObjList;
	ID3D11DeviceContext* _pContext = nullptr;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Load(C_STR filename);
	void PreProcess(FbxNode* pFbxNode);
	void ParseMesh(FbxMesh* pFbxMesh);
	//FbxVector2 ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* VertexUVSet);
	FbxVector2 ReadTextureCoord(FbxMesh* pFbxMesh,
		FbxLayerElementUV* VertexUVSet,
		int posIndex,
		int uvIndex);
	FbxColor ReadColor(FbxMesh* pFbxMesh,
		FbxLayerElementVertexColor* VertexColorSet,
		int posIndex,
		int ColorIndex);
	FbxVector4 ReadNormal(FbxMesh* pFbxMesh,
		FbxLayerElementNormal* VertexNormalSet,
		int posIndex,
		int colorIndex);
	int GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* MaterialSet);
};

