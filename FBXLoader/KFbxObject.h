#pragma once
#include <fbxsdk.h>
#include "Object3D.h"

class KFbxObject : public Object3D
{
public:
	FbxNode* _pFbxNode = nullptr;
	FbxNode* _pFbxParentNode = nullptr;
	KFbxObject* _pParent = nullptr;
	std::vector<KFbxObject*> _pFbxChilds;
	void SetParent(KFbxObject* pParentNode)
	{
		pParentNode->_pFbxChilds.push_back(this);
		_pParent = pParentNode;
	}

public:
	std::vector<ID3D11Buffer*> _pSubVB;
	std::vector<std::vector<PNCT_VERTEX>> vbDataList;
	std::vector<Texture*> _pSubTexture;
	std::vector<W_STR> vbTexList;

public:
	void CreateVertexData();
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();
	bool LoadTexture(W_STR texturename);
	bool PostRender();
	bool Release();
};