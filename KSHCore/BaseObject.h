#pragma once
#include "Device.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "Collision.h"

struct SimpleVertex
{
	Vector3D p;
	Vector4D c;
	Vector2D t;
	SimpleVertex() {}
	SimpleVertex(Vector3D vp, Vector4D vc, Vector2D vt)
	{
		p = vp;
		c = vc;
		t = vt;
	}
};
struct PNCT_VERTEX
{
	Vector3D p;
	Vector3D n;
	Vector4D c;
	Vector2D t;
	PNCT_VERTEX() {}
	PNCT_VERTEX(Vector3D vp, Vector3D vn, Vector4D vc, Vector2D vt)
	{
		p = vp;
		n = vn;
		c = vc;
		t = vt;
	}
};

//GPU의 bandwidth와 CPU의 사용량을 최소화 할 수 있음
//4개의 실수 단위로 넘겨야 됨
//쉐이더에서 cbuffer 시멘틱을 사용함 각 변수들은 전역변수 처럼 간단히 사용하게 됨
struct VS_CONSTANT_BUFFER
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;
	float x;
	float y;
	float z;
	float fTimer;
};
namespace KDX
{
	ID3D11Buffer* CreateVertexBuffer(ID3D11Device* pd3dDevice, void* pDataAddress, UINT iNumVertex, UINT iVertexSize);

	class BaseObject
	{
	public:
		bool _IsNullable = true;
		Matrix _matWorld;
		Matrix _matView;
		Matrix _matProj;
		DWORD _dwFace;

	public:
		ID3D11Device* _pd3dDevice = nullptr;
		ID3D11DeviceContext* _pImmediateContext = nullptr;
		ID3D11Buffer* _pVertexBuffer = nullptr;
		ID3D11Buffer* _pIndexBuffer = nullptr;
		VS_CONSTANT_BUFFER _cbData;
		//상수버퍼를 선언하고 생성해야 함
		ID3D11Buffer* _pConstantBuffer = nullptr;
		ID3D11InputLayout* _pVertexLayout = nullptr;
		Shader* _pShader = nullptr;
		Texture* _pTexture = nullptr;
		std::wstring _szShaderName;
		std::wstring _szTextureName;
		ID3D11ShaderResourceView* _pTextureSRV = nullptr;
		std::vector<PNCT_VERTEX> _VertexList;
		std::vector<PNCT_VERTEX> _InitVertexList;
		std::vector<DWORD> _IndexList;
		float _fAngleDegree = 0.0f;
		Rect _rtCollision;

	public:
		ID3D11VertexShader* _pVS = nullptr;
		ID3D11PixelShader* _pPS = nullptr;
		ID3DBlob* _pVSCode = nullptr;
		ID3DBlob* _pPSCode = nullptr;

	public:
		virtual bool Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, const std::wstring& shaderName, const std::wstring& textureName);
		virtual void CreateVertexData();
		virtual void CreateIndexData();
		virtual void CreateConstantData();
		virtual HRESULT CreateVertexBuffer();
		virtual HRESULT CreateIndexBuffer();
		virtual HRESULT CreateConstantBuffer();
		virtual HRESULT CreateShader(const std::wstring& filename);
		virtual HRESULT CreateVertexShader(const std::wstring& filename);
		virtual HRESULT CreatePixelShader(const std::wstring& filename);
		virtual HRESULT CreateVertexLayout();
		virtual void UpdateVertexBuffer();
		virtual void UpdateConstantBuffer();
		virtual void Rotation();
		virtual bool LoadTexture(W_STR texturename);

	public:
		virtual bool Init();
		virtual bool Frame();
		virtual bool PreRender();
		virtual bool Render();
		virtual bool PostRender();
		virtual bool Release();
		virtual void SetMatrix(Matrix* matWorld, Matrix* matView, Matrix* matProj);

	public:
		BaseObject()
		{
			_IsNullable = false;
		}
	};
}

using namespace KDX;

