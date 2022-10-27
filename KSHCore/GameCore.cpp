#include "GameCore.h"

bool GameCore::CoreInit()
{
    HRESULT hr;
    if (Device::Init() == false)
    {
        return false;
    }
    DxState::SetState(_pd3dDevice.Get());

    I_Sprite.SetDevice(_pd3dDevice.Get(), _pImmediateContext.Get());
    I_Tex.SetDevice(_pd3dDevice.Get(), _pImmediateContext.Get());
    I_Shader.SetDevice(_pd3dDevice.Get(), _pImmediateContext.Get());
    I_Sound.Init();
    I_Timer.Init();
    I_Input.Init();
    _Writer.Init();

    IDXGISurface1* pBackBuffer;
    _pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1),
        (void**)&pBackBuffer);
    _Writer.Set(pBackBuffer);
    pBackBuffer->Release();

    std::wstring shaderfilename = L"../../data/shader/DefaultRT.hlsl";
    _BG.Create(_pd3dDevice.Get(), _pImmediateContext.Get(), shaderfilename, L"../../data/_RAINBOW.bmp");
    _RT.Create(_pd3dDevice.Get(), _pImmediateContext.Get(), 2048, 2048);
    return Init();
}

bool GameCore::CoreFrame()
{
    I_Timer.Frame();
    I_Input.Frame();
    I_Sound.Frame();
    _Writer.Frame();
    return Frame();
}

bool GameCore::CorePreRender()
{
    _pImmediateContext->OMSetRenderTargets(1, _pRTV.GetAddressOf(), _pDepthStencilView.Get());
    float color[4] = { 0.34324f,0.52342f,0.798320f,1.0f };

    //ClearRenderTargetView
    //ID3D11RenderTargetView* pRenderTargetView // ·»´õÅ¸°Ùºä¿¡ ´ëÇÑ Æ÷ÀÎÅÍ
    //FLOAT ColorRGBA[4] //·»´õÅ¸°Ùºä¸¦ Ã¤¿ï »ö»ó °ª
    _pImmediateContext->ClearRenderTargetView(_pRTV.Get(), color);
    //_pImmediateContext->PSSetSamplers(0, 1, &DxState::g_pDefaultSSWrap);
    _pImmediateContext->ClearDepthStencilView(_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    _pImmediateContext->PSSetSamplers(0, 1, &DxState::g_pDefaultSSMirror);
    _pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    _pImmediateContext->RSSetViewports(1, &_vp);
    _pImmediateContext->RSSetState(DxState::g_pDefaultRSSolid);
    _pImmediateContext->OMSetBlendState(DxState::g_pAlphaBlend, 0, -1);
    _pImmediateContext->OMSetDepthStencilState(DxState::g_pDefaultDepthStencil, 0xff);
    return true;
}

bool GameCore::CoreRender()
{
    CorePreRender();
    // ·£´õÅ¸ÄÏ ÁöÁ¤
    _RT._pOldRTV = _pRTV.Get();
    _RT._pOldDSV = _pDepthStencilView.Get();
    _RT._vpOld[0] = _vp;

    if (_RT.Begin(_pImmediateContext.Get()))
    {
        Render();
        _RT.End(_pImmediateContext.Get());
    }

    if (_RT._pSRV)
    {
        _BG._pTextureSRV = _RT._pSRV.Get();
        //_BG._pTextureSRV = _RT._pDsvSRV.Get();
    }
    /*I_Timer.Render();
    I_Input.Render();
    _Writer._szDefaultText = I_Timer._szTimer;
    _Writer.Render();*/
    CorePostRender();
    return true;
}

bool GameCore::CorePostRender()
{
    _BG.SetMatrix(nullptr, nullptr, nullptr);
    _BG.Render();

    I_Timer.Render();
    I_Input.Render();
    _Writer._szDefaultText = I_Timer._szTimer;
    _Writer.Render();

    _pSwapChain->Present(0, 0);
    return true;
}

bool GameCore::CoreRelease()
{
    _RT.Release();
    _BG.Release();
    Release();
    I_Timer.Release();
    I_Input.Release();
    _Writer.Release();
    DxState::Release();
    Device::Release();
    return true;
}

bool GameCore::Run()
{
    if (CoreInit() == false)
    {
        CoreRelease();
        return false;
    }
    MSG msg = { 0, };
    _bGameRun = true;
    while (_bGameRun)
    {
        if (Window::Run() == false)
        {
            _bGameRun = false;
        }
        else
        {
            if (!CoreFrame() || !CoreRender())
            {
                _bGameRun = false;
            }
        }
    }
    CoreRelease();
    return true;
}

HRESULT GameCore::CreateDXResource()
{
    _Writer.Init();
    IDXGISurface1* pBackBuffer;
    _pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&pBackBuffer);
    _Writer.Set(pBackBuffer);
    pBackBuffer->Release();
    return S_OK;
}

HRESULT GameCore::DeleteDXResource()
{
    _Writer.DeleteDXResource();
    return S_OK;
}
