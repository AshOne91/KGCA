#include "Shader.h"

bool Shader::Init()
{
	return true;
}

bool Shader::Frame()
{
	return true;
}

bool Shader::Render()
{
	return true;
}

bool Shader::Release()
{
	if (_pVS) _pVS->Release();
	if (_pPS) _pPS->Release();
	if (_pVSCode) _pVSCode->Release();
	if (_pPSCode) _pPSCode->Release();

	_pVS = nullptr;
	_pPS = nullptr;
	_pVSCode = nullptr;
	_pPSCode = nullptr;

	return true;
}

HRESULT Shader::Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, const std::wstring& name)
{
	HRESULT hr;
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmediateContext;

	ID3DBlob* pErrorCode = nullptr;
	hr = D3DCompileFromFile(
		name.c_str(),
		NULL,
		NULL,
		"VS",
		"vs_5_0",
		0,
		0,
		&_pVSCode,
		&pErrorCode);
	if (FAILED(hr))
	{
		if (pErrorCode)
		{
			OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
			pErrorCode->Release();
		}
		return hr;
	}

	hr = _pd3dDevice->CreateVertexShader(_pVSCode->GetBufferPointer(), _pVSCode->GetBufferSize(), NULL, &_pVS);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = D3DCompileFromFile(
		name.c_str(),
		NULL,
		NULL,
		"PS",
		"ps_5_0",
		0,
		0,
		&_pPSCode,
		&pErrorCode);
	if (FAILED(hr))
	{
		if (pErrorCode)
		{
			OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
			pErrorCode->Release();
		}
		return hr;
	}
	hr = _pd3dDevice->CreatePixelShader(_pPSCode->GetBufferPointer(), _pPSCode->GetBufferSize(), NULL, &_pPS);
	if (FAILED(hr))
	{
		return hr;
	}
	return hr;
}