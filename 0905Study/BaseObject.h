#pragma once
#include "Texture.h"
#include "Shader.h"
#include "Vector.h"
// p(위치)n(노말)c(컬러)t(텍스처좌표)
struct SimpleVertex
{
	//무조건 무상속 객체여야 함
	//상속을 받을시 사이즈가 vptr부터 잡혀 virtual로 사용하면 안됨
	Vector3D p;
	Vector4D c;
	Vector2D t;
};
class BaseObject
{
public:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);

public:
	Texture* _pTexture;
	std::vector<SimpleVertex> _vertexList;
	ID3D11Buffer* _pVertexBuffer;
	ID3D11InputLayout* _pVertexLayout;
	Shader* _pShader;

public:
	HRESULT CreateVertexBuffer();
	bool CreateShader(std::wstring filename);
	HRESULT CreateVertexLayout();
	bool LoadTexture(std::wstring filename);

public:
	virtual bool Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext, const std::wstring& textName, const std::wstring& shaderName);

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool PreRender();
	virtual bool Render();
	virtual bool PostRender();
	virtual bool Release();
};

