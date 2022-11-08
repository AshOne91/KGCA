#pragma once
#include <fbxsdk.h>
#include "Object3D.h"

struct AnimTrack
{
	UINT iFrame; //fTime;
	TBASIS_EX::TMatrix matAnim; // self * parent;
	TBASIS_EX::TMatrix matSelfAnim; // matAnim * inv(parent)
	TBASIS_EX::TVector3 t; // self
	TBASIS_EX::TQuaternion r; // self
	TBASIS_EX::TVector3 s; //self
};

struct AnimScene
{
	UINT iStartFrame;
	UINT iEndFrame;
	float fTickPerFrame; // 160
	float fFrameSpeed; // 30
};

class KFbxObject : public Object3D
{
public:
	TMatrix _matAnim;
	TMatrix _matControl;
	AnimScene _AnimScene;
	float _fAnimFrame = 0;
	float _fAnimInverse = 1.0f;
	float _fAnimSpeed = 1.0f;
	FbxAMatrix _fbxLocalMatrix;
	FbxNode* _pFbxNode = nullptr;
	FbxNode* _pFbxParentNode = nullptr;
	KFbxObject* _pParent = nullptr;
	std::vector<KFbxObject*> _pFbxChilds;
	std::vector<AnimTrack> _AnimTracks;
	void SetParent(KFbxObject* pParentNode)
	{
		pParentNode->_pFbxChilds.push_back(this);
		_pParent = pParentNode;
	}
	TMatrix Interplate(float fFrame);

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