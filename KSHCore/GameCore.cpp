#include "GameCore.h"
#include "Timer.h"
#include "Input.h"
#include "TextureManager.h"

bool GameCore::CoreInit()
{
    HRESULT hr;
    if (Device::Init() == false)
    {
        return false;
    }
    I_Tex.SetDevice(_pd3dDevice, _pImmediateContext);
    I_Timer.Init();
    I_Input.Init();
    _Writer.Init();

    IDXGISurface1* pBackBuffer;
    _pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1),
        (void**)&pBackBuffer);
    _Writer.Set(pBackBuffer);
    pBackBuffer->Release();
    return Init();
}

bool GameCore::CoreFrame()
{
    I_Timer.Frame();
    I_Input.Frame();
    _Writer.Frame();
    return Frame();
}

bool GameCore::CorePreRender()
{
    _pImmediateContext->OMSetRenderTargets(1, &_pRTV, NULL);
    float color[4] = { 1.0f,1.0f,1.0f,1.0f };

    //ClearRenderTargetView
    //ID3D11RenderTargetView* pRenderTargetView // ����Ÿ�ٺ信 ���� ������
    //FLOAT ColorRGBA[4] //����Ÿ�ٺ並 ä�� ���� ��
    _pImmediateContext->ClearRenderTargetView(_pRTV, color);
    _pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    //_pImmediateContext->PSSetSamplers(0, 1, &DxState::g_pDefaultSS);
    return true;
}

bool GameCore::CoreRender()
{
    CorePreRender();
    Render();
    I_Timer.Render();
    I_Input.Render();
    _Writer._szDefaultText = I_Timer._szTimer;
    _Writer.Render();
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
    Release();
    I_Timer.Release();
    I_Input.Release();
    _Writer.Release();
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