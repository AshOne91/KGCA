#include "DxState.h"
ID3D11SamplerState* DxState::g_pDefaultSSWrap = nullptr;
ID3D11SamplerState* DxState::g_pDefaultSSMirror = nullptr;

ID3D11RasterizerState* DxState::g_pDefaultRSWireFrame = nullptr;
ID3D11RasterizerState* DxState::g_pDefaultRSSolid = nullptr;

ID3D11BlendState* DxState::g_pDefaultBS = nullptr;

bool DxState::SetState(ID3D11Device* pd3dDevice)
{
	HRESULT hr;
	// SS
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; // 최근점 필터링
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	hr = pd3dDevice->CreateSamplerState(&sd, &g_pDefaultSSWrap);
	if (FAILED(hr))
	{
		return false;
	}

	sd.Filter = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
	hr = pd3dDevice->CreateSamplerState(&sd, &g_pDefaultSSMirror);
	if (FAILED(hr))
	{
		return false;
	}

	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.DepthClipEnable = TRUE;
	rd.FillMode = D3D11_FILL_WIREFRAME;
	rd.CullMode = D3D11_CULL_NONE;
	pd3dDevice->CreateRasterizerState(&rd, &g_pDefaultRSWireFrame);

	rd.FillMode = D3D11_FILL_SOLID;
	pd3dDevice->CreateRasterizerState(&rd, &g_pDefaultRSSolid);

	return true;
}

bool DxState::Release()
{
	if (g_pDefaultSSWrap) g_pDefaultSSWrap->Release();
	if (g_pDefaultSSMirror) g_pDefaultSSMirror->Release();
	if (g_pDefaultRSWireFrame) g_pDefaultRSWireFrame->Release();
	if (g_pDefaultRSSolid) g_pDefaultRSSolid->Release();
	if (g_pDefaultBS) g_pDefaultBS->Release();

	g_pDefaultSSWrap = nullptr;
	g_pDefaultSSMirror = nullptr;
	g_pDefaultRSWireFrame = nullptr;
	g_pDefaultRSSolid = nullptr;
	g_pDefaultBS = nullptr;
	return true;
}