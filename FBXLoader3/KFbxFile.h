#pragma once
#include "Std.h"
#include <fbxsdk.h>
#include "KFbxObject.h"
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "zlib-md.lib")

class KFbxFile
{
public:
	TMatrix _matWorld;
	TMatrix _matView;
	TMatrix _matProj;

public:
	AnimScene _AnimScene;
	float _fAnimFrame = 0;
	float _fAnimInverse = 1.0f;
	float _fAnimSpeed = 1.0f;

public:
	FbxManager* _pFbxManager;
	FbxImporter* _pFbxImporter;
	FbxScene* _pFbxScene;
	FbxNode* _pRootNode;

	std::map<FbxNode*, FbxObjectSkinning*> _pObjectMap;
	std::map<FbxNode*, UINT> _pObjectIDMap;
	std::vector<FbxObjectSkinning*> _pObjectList;
	std::vector<FbxObjectSkinning*> _pDrawObjList;
	ID3D11DeviceContext* _pContext = nullptr;

	VS_CONSTANT_BONE_BUFFER _cbDataBone;
	ID3D11Buffer* _pAnimBoneCB;
	HRESULT CreateConstantBuffer(ID3D11Device* pDevice);
	// ���� �������� ��ȯ�ϴ� ����� ����ȴ�.
	//std::map<FbxNode*, TMatrix> _dxMatrixBindPseMap;
	//std::map<std::wstring, TMatrix> _dxMatrixBindPseMap;
	void SetMatrix(TMatrix* matWorld, TMatrix* matView, TMatrix* matProj);

	void UpdateSkeleton(ID3D11DeviceContext* pContext,
		float fTime,
		VS_CONSTANT_BONE_BUFFER& cbData);
	void UpdateSkinning(ID3D11DeviceContext* pContext,
		VS_CONSTANT_BONE_BUFFER& cbInputData,
		std::vector<VS_CONSTANT_BONE_BUFFER>& cbOutputData);

public:
	bool Init();
	bool UpdateFrame(ID3D11DeviceContext* pContext);
	bool UpdateFrame(ID3D11DeviceContext* pContext, float fFrame);
	bool Render(ID3D11DeviceContext* pContext);
	bool Release();
	bool Load(C_STR filename);
	void PreProcess(FbxNode* pFbxNode);
	void ParseMesh(FbxMesh* pFbxMesh, FbxObjectSkinning* pObject);
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
	void InitAnimation();
	//void LoadAnimation(FbxObjectSkinning* pObj);
	void LoadAnimation(FbxLongLong t, FbxTime time);
	TMatrix ConvertMatrix(FbxAMatrix& fbxMatrix);
	TMatrix DxConvertMatrix(FbxAMatrix& fbxMatrix);

	bool ParseMeshSkinning(FbxMesh* pFbxMesh, FbxObjectSkinning* pObject);
};

