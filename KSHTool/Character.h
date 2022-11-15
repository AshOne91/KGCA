#pragma once
#include "KFbxFile.h"

struct ActionTable
{
	UINT iStartFrame;
	UINT iEndFrame;
	float fTickPerFrame;
	float fFrameSpeed;
	bool bLoop;
	ActionTable() :iStartFrame{ 0 }
		, iEndFrame{ 0 }
		, fTickPerFrame{ 0.0 }
		, fFrameSpeed{ 0.0 }
		, bLoop{false}
	{}
};

class Character
{
public:
	UINT _iFbxListID;
	KFbxFile* _pFbxFile = nullptr;

public:
	TMatrix _matWorld;
	TMatrix _matView;
	TMatrix _matProj;

public:
	ActionTable _ActionCurrent;
	AnimScene _AnimScene;
	float _fAnimFrame = 0;
	UINT _iStartFrame;
	UINT _iEndFrame;
	float _fAnimInverse = 1.0f;
	float _fAnimSpeed = 1.0f;

	KFbxFile* _pAnionFbxFile = nullptr;
	std::map<std::wstring, KFbxFile*> _ActionFileList;
	std::map<std::wstring, ActionTable> _ActionList;

	VS_CONSTANT_BONE_BUFFER _cbDataBone;
	std::vector<VS_CONSTANT_BONE_BUFFER> _cbDrawGeom;

	ID3D11Buffer* _pAnimBoneCB;
	std::vector<ID3D11Buffer*> _pSkinBoneCB;

public:
	HRESULT CreateConstantBuffer(ID3D11Device* pDevice);
	bool UpdateFrame(ID3D11DeviceContext* pContext);
	void SetMatrix(TMatrix* matWorld, TMatrix* matView, TMatrix* matProj);
	bool Render(ID3D11DeviceContext* pContext);
	bool Release();
};

