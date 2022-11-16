#pragma once
#include "TStd.h"

struct SimpleVertex
{
	TVector2 v;
	TVector2 t;
};

struct TVertex
{
	TVector3 p; // ��ġ
	TVector3 n; // �븻
	TVector4 c; // �÷�
	TVector2 t; // �ؼ�
	TVertex(TVector3 p1, TVector3 n1, TVector4 c1, TVector2 t1)
	{
		p = p1;
		n = n1;
		c = c1;
		t = t1;
	}
};

enum TCollisionType
{
	Block = 0,
	Overlap,
	Ignore
};

enum TSelectType
{
	Select_Block = 0,
	Select_Overlap,
	Select_Ignore
};

enum TSelectState
{
	T_DEFAULT = 0,  // Ŀ���� ���� ���� ��(T_FOCUS���¿��� �ٸ� ���� T_ACTIVE�ϸ� ��ȯ�ȴ�.)
	T_HOVER = 1,	// Ŀ���� ���� ���� ��
	T_FOCUS = 2,	// T_ACTIVE���¿��� ���� ��ư�� �ٸ� ������ ������ ��(���)
	T_ACTIVE = 4,	// ���콺 ���� ��ư ������ ���� ��
	T_SELECTED = 8, // T_ACTIVE ���¿��� ���ɹ�ư ������ ��
};

class TBaseObject
{
public:
	std::wstring m_csName;

public:
	TBaseObject* m_pParent = nullptr;
	bool m_bDead;
	int m_iCollisionID;
	int m_iSelectID;
	float		m_fSpeed;
	float		m_fWidth;
	float		m_fHeight;
	TRect		m_rtCollision;
	TBox		m_BoxCollision;
	DWORD		m_dwCollisonType;
	DWORD		m_dwSelectType;
	DWORD		m_dwSelectState;
	DWORD		m_dwPreSelectState;
	bool		m_bSelect;
	bool		m_bAlphaBlend;
public:
	virtual void	HitOverlap(TBaseObject* pObj, DWORD dwState);
	virtual void	HitSelect(TBaseObject* pObj, DWORD dwState);
	virtual void	SetCollisionType(DWORD dwCollisionType, DWORD dwSelectType)
	{
		m_dwCollisonType = dwCollisionType;
		m_dwSelectType = dwSelectType;
	}
public:

	TBaseObject()
	{
		m_bDead = false;
		m_bSelect = false;
		m_bAlphaBlend = true;
		m_dwSelectState = T_DEFAULT;
		m_iCollisionID = -1;
		m_iSelectID = -1;
		m_dwCollisonType = TCollisionType::Ignore;
		m_dwSelectType = TSelectType::Select_Ignore;
	}
};

struct TIndex
{
	DWORD _0;
	DWORD _1;
	DWORD _2;
};

struct TConstantData
{
	TMatrix matWorld;
	TMatrix matView;
	TMatrix matProj;
	TMatrix matNormal;
	TVector4 Color;
	TVector4 Timer;
};

struct TBoneWorld
{
	TMatrix matBoneWorld[255];
};

struct TLightData
{
	TVector4 vLightDir;
	TVector4 vLightPos;
	TVector4 vCameraDir;
	TVector4 vCameraPos;
	TMatrix matLight; // w*v*p*t
};

class TDxObject : public TBaseObject
{
public:
	TTexture* m_pColorTex = nullptr;
	TTexture* m_pMaskTex = nullptr;
	TShader* m_pVShader = nullptr;
	TShader* m_pPShader = nullptr;
	D3D11_TEXTURE2D_DESC		m_TextureDesc;

public:
	std::vector<SimpleVertex> m_InitScreenList;
	std::vector<TVertex> m_VertexList;

	ID3D11Buffer* m_pVertexBuffer = nullptr;

	std::vector<DWORD> m_IndexList;
	ID3D11Buffer* m_pIndexBuffer = nullptr;

	TConstantData _pConstantList;




};

