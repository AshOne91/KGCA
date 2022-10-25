#include "RenderTarget.h"

bool RenderTarget::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, FLOAT fWidth, FLOAT fHeight)
{
    HRESULT hr;
    _Viewport.Width = fWidth;
    _Viewport.Height = fHeight;
    _Viewport.TopLeftX = 0;
    _Viewport.TopLeftY = 0;
    _Viewport.MinDepth = 0.0f;
    _Viewport.MaxDepth = 1.0f;

    _TexDesc.Width = (UINT)fWidth;
    _TexDesc.Height = (UINT)fHeight;
    _TexDesc.MipLevels = 1;
    _TexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    _TexDesc.SampleDesc.Count = 1;
    _TexDesc.SampleDesc.Quality = 0;
    _TexDesc.Usage = D3D11_USAGE_DEFAULT;
    _TexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    _TexDesc.CPUAccessFlags = 0;
    _TexDesc.MiscFlags = 0;
    _TexDesc.ArraySize = 1;

    if (FAILED(hr = pd3dDevice->CreateTexture2D(&_TexDesc, NULL, _pTexture.GetAddressOf())))
    {
        return hr;
    }
    if (FAILED(hr = pd3dDevice->CreateShaderResourceView(_pTexture.Get(), NULL, _pSRV.GetAddressOf())))
    {
        return hr;
    }
    if (FAILED(hr = pd3dDevice->CreateRenderTargetView(_pTexture.Get(), NULL, _pRenderTargetView.GetAddressOf())))
    {
        return hr;
    }

    //Depth Buffer
    ComPtr<ID3D11Texture2D> pDSTexture = nullptr;
    D3D11_TEXTURE2D_DESC DescDepth;
    DescDepth.Width = fWidth;
    DescDepth.Height = fHeight;
    DescDepth.MipLevels = 1;
    DescDepth.ArraySize = 1;
    DescDepth.Format = DXGI_FORMAT_R24G8_TYPELESS;
    DescDepth.SampleDesc.Count = 1;
    DescDepth.SampleDesc.Quality = 0;
    DescDepth.Usage = D3D11_USAGE_DEFAULT;
    // 백 버퍼 깊이 및 스텐실 버퍼 생성
    DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
    DescDepth.CPUAccessFlags = 0;
    DescDepth.MiscFlags = 0;
    if (FAILED(hr = pd3dDevice->CreateTexture2D(&DescDepth, NULL, &pDSTexture)))
    {
        return hr;
    }
    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
    ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
    dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    if (FAILED(hr = pd3dDevice->CreateDepthStencilView(pDSTexture.Get(), &dsvDesc, &_pDepthStencilView)))
    {
        return hr;
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;
    srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    if (FAILED(hr = pd3dDevice->CreateShaderResourceView(pDSTexture.Get(), &srvDesc, &_pDsvSRV)))
    {
        return hr;
    }

    return true;
}

bool RenderTarget::Begin(ID3D11DeviceContext* pContext)
{
    /*UINT iNumViewport = 1;
    pContext->OMGetRenderTargets(1, &m_pOldRTV, &m_pOldDSV);
    pContext->RSGetViewports(&iNumViewport, m_vpOld);*/

    ID3D11RenderTargetView* pNullRTV = NULL;
    pContext->OMSetRenderTargets(1, &pNullRTV, NULL);
    pContext->OMSetRenderTargets(1, _pRenderTargetView.GetAddressOf(), _pDepthStencilView.Get());
    const FLOAT color[] = { 1, 1, 1, 1 };
    pContext->ClearRenderTargetView(_pRenderTargetView.Get(), color);
    pContext->ClearDepthStencilView(_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);
    pContext->RSSetViewports(1, &_Viewport);
    return true;
}

bool RenderTarget::End(ID3D11DeviceContext* pContext)
{
    pContext->OMSetRenderTargets(1, &_pOldRTV, _pOldDSV);
    pContext->RSSetViewports(1, _vpOld);
    /*m_pOldRTV->Release();
    m_pOldDSV->Release();*/
    return true;
}

bool RenderTarget::Release()
{
    return true;
}
