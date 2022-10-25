#pragma once
#include "BaseObject.h"

class RenderTarget
{
public:
	ComPtr<ID3D11RenderTargetView> _pRenderTargetView;
	ComPtr<ID3D11DepthStencilView> _pDepthStencilView;
	ComPtr<ID3D11ShaderResourceView> _pSRV;
	ComPtr<ID3D11ShaderResourceView> _pDsvSRV; // ±Ì¿Ãπˆ∆€ ∏Æº“Ω∫∫‰
	ComPtr<ID3D11Texture2D> _pTexture;
	D3D11_DEPTH_STENCIL_VIEW_DESC _DepthStencilDesc;
	D3D11_TEXTURE2D_DESC _TexDesc;
	D3D11_VIEWPORT _Viewport;

	ID3D11RenderTargetView* _pOldRTV;
	ID3D11DepthStencilView* _pOldDSV;
	D3D11_VIEWPORT _vpOld[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];

public:
	bool Create(ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pImmediateContext,
		FLOAT fWidth = 1024.0f, FLOAT fHeight = 1024.0f);
	bool Begin(ID3D11DeviceContext* pContext);
	bool End(ID3D11DeviceContext* pContext);
	bool Release();
};

