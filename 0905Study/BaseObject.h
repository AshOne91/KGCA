#pragma once
#include "Texture.h"
#include "Shader.h"
#include "Vector.h"
// p(��ġ)n(�븻)c(�÷�)t(�ؽ�ó��ǥ)
struct SimpleVertex
{
	//������ ����� ��ü���� ��
	//����� ������ ����� vptr���� ���� virtual�� ����ϸ� �ȵ�
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

