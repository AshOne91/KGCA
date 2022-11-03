#pragma once
#include "Std.h"
#include <fbxsdk.h>
#include "KFbxObject.h"
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "zlib-md.lib")

class FbxLoader
{
public:
	FbxManager* _pFbxManager;
	FbxImporter* _pFbxImporter;
	FbxScene* _pFbxScene;
	FbxNode* _pRootNode;
	std::map<FbxNode*, KFbxObject*> _pObjectMap;
	std::vector<KFbxObject*> _pObjectList;

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
	void ParseMesh(FbxMesh* pFbxMesh, KFbxObject* pObject);
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

