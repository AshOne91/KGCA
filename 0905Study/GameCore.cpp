#include "GameCore.h"
#include "Timer.h"
#include "Input.h"
#include "DxState.h"
#include "TextureManager.h"
#include "ShaderManager.h"

bool GameCore::CoreInit()
{
    HRESULT hr;
    if (Device::Init() == false)
    {
        return false;
    }
    I_Tex.SetDevice(_pd3dDevice, _pImmediateContext);
    I_Shader.SetDevice(_pd3dDevice, _pImmediateContext);
    DxState::SetState(_pd3dDevice);

    I_Timer.Init();
    I_Input.Init();
    _writer.Init();

    _pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&_pBackBuffer);
    _pImmediateContext->OMSetRenderTargets(1, &_pRTV, NULL);
    _writer.Set(_pBackBuffer);
    return Init();
}

bool GameCore::CoreFrame()
{
    I_Timer.Frame();
    I_Input.Frame();
    _writer.Frame();
    return Frame();
}

bool GameCore::CorePreRender()
{
    //_pImmediateContext->OMSetRenderTargets(1, &_pRTV, NULL);
    float color[4] = { 1.0f,1.0f,1.0f,1.0f };

    //ClearRenderTargetView
    //ID3D11RenderTargetView* pRenderTargetView // ·»´õÅ¸°Ùºä¿¡ ´ëÇÑ Æ÷ÀÎÅÍ
    //FLOAT ColorRGBA[4] //·»´õÅ¸°Ùºä¸¦ Ã¤¿ï »ö»ó °ª
    _pImmediateContext->ClearRenderTargetView(_pRTV, color);
    _pImmediateContext->PSSetSamplers(0, 1, &DxState::g_pDefaultSS);
    return true;
}

bool GameCore::CoreRender()
{
    CorePreRender();
    Render();
    I_Timer.Render();
    I_Input.Render();
    _writer._szDefaultText = I_Timer._szTimer;
    _writer.Render();
    CorePostRender();
    return true;
}

bool GameCore::CorePostRender()
{
    _pSwapChain->Present(0, 0);
    return true;
}

bool GameCore::CoreRelease()
{
    _pBackBuffer->Release();
    Release();
    I_Timer.Release();
    I_Input.Release();
    DxState::Release();
    _writer.Release();
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
