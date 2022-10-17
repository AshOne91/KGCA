#include "DxState.h"
ID3D11SamplerState* DxState::g_pDefaultSSWrap = nullptr;
ID3D11SamplerState* DxState::g_pDefaultSSMirror = nullptr;

ID3D11RasterizerState* DxState::g_pDefaultRSWireFrame = nullptr;
ID3D11RasterizerState* DxState::g_pDefaultRSSolid = nullptr;

ID3D11BlendState* DxState::g_pAlphaBlend = nullptr;

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

	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
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
	rd.CullMode = D3D11_CULL_BACK;
	pd3dDevice->CreateRasterizerState(&rd, &g_pDefaultRSWireFrame);

	rd.FillMode = D3D11_FILL_SOLID;
	pd3dDevice->CreateRasterizerState(&rd, &g_pDefaultRSSolid);

	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	//bd.IndependentBlendEnable = TRUE;
	// 혼합 : 섞는다.
	// 배경(목적지) d-RGBA : 백버퍼에 이미 랜더링 되어 있는 결과
	// 현재 소스 : s_RGBA : 지금 랜더링 하려는 객체, 픽셀쉐이더
	// RGB 성분을 혼합하는 명령
	// 알파블랜딩 공식
	// finalColor = SrcColor*SrcAlpha+DestColor*(1.0f-SrcApha);
	// apha = 1.0f (불투명), alpha = 0.0f (투명), alpha 0-1 (반투명)
	// finalColor = SrcColor*1.0f+DestColor*(1.0f-1.0f);
	// finalColor = SrcColor*0.0f+DestColor*(1.0f-0.0f);
	// finalColor = SrcColor*0.5f+DestColor*(1.0f-0.5f);
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	// 알파 성분을 혼합하는 명령
	// finalAlpha = SrcAlpha*1.0f+DestAlpha*0.0f;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	pd3dDevice->CreateBlendState(&bd, &g_pAlphaBlend);

	return true;
}

bool DxState::Release()
{
	if (g_pDefaultSSWrap) g_pDefaultSSWrap->Release();
	if (g_pDefaultSSMirror) g_pDefaultSSMirror->Release();
	if (g_pDefaultRSWireFrame) g_pDefaultRSWireFrame->Release();
	if (g_pDefaultRSSolid) g_pDefaultRSSolid->Release();
	if (g_pAlphaBlend) g_pAlphaBlend->Release();

	g_pDefaultSSWrap = nullptr;
	g_pDefaultSSMirror = nullptr;
	g_pDefaultRSWireFrame = nullptr;
	g_pDefaultRSSolid = nullptr;
	g_pAlphaBlend = nullptr;
	return true;
}