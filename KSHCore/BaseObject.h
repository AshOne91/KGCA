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
};

class BaseObject
{
public:
	bool _IsNullable = true;

public:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	ID3D11Buffer* _pVertexBuffer = nullptr;
	ID3D11Buffer* _pIndexBuffer = nullptr;
	ID3D11InputLayout* _pVertexLayout = nullptr;
	Shader* _pShader = nullptr;
	Texture* _pTexture = nullptr;
	std::wstring _szShaderName;
	std::wstring _szTextureName;
	ID3D11ShaderResourceView* _pTextureSRV = nullptr;
	std::vector<SimpleVertex> _VertexList;
	std::vector<SimpleVertex> _InitVertexList;
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
	virtual HRESULT CreateVertexBuffer();
	virtual HRESULT CreateIndexBuffer();
	virtual HRESULT CreateShader(const std::wstring& filename);
	virtual HRESULT CreateVertexShader(const std::wstring& filename);
	virtual HRESULT CreatePixelShader(const std::wstring& filename);
	virtual HRESULT CreateVertexLayout();
	virtual void UpdateVertexBuffer();
	virtual void Rotation();

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool PreRender();
	virtual bool Render();
	virtual bool PostRender();
	virtual bool Release();

public:
	BaseObject()
	{
		_IsNullable = false;
	}
};

