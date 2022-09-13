#pragma once
#include "Std.h"

class Shader
{
public:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

	ID3D11VertexShader* _pVS = nullptr;
	ID3D11PixelShader* _pPS = nullptr;
	ID3DBlob* _pVSCode = nullptr;
	ID3DBlob* _pPSCode = nullptr;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	HRESULT Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, const std::wstring& name);

};

