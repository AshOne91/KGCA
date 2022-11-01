#pragma once
#include "Std.h"
#include <fbxsdk.h>
#include "Object3D.h"
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "zlib-md.lib")

class KFbxObject : public BaseObject
{
public:
	std::vector<KFbxObject*> _pDrawChild;
	std::vector<std::vector<SimpleVertex>> vbDataList;
	std::vector<W_STR> vbTexList;

public:
	void CreateVertexData() {}
	HRESULT CreateIndexBuffer()
	{
		return S_OK;
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
	int GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* MaterialSet);
};

