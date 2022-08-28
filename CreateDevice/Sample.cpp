#include "Sample.h"
bool		Sample::Init()
{
    HRESULT hr;
    D3D_FEATURE_LEVEL pFeatureLevel; // 어떤 버전이 될지 확인가능
    IDXGIAdapter* pAdapter = nullptr; // 그래픽 카드(그래픽카드 조회 가능)
    D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE; //하드웨어 성능(그래픽카드의 성능) 하드웨어 가속(GPU), 소프트웨어(CPU)
    HMODULE Software = NULL;//다른 버전의 엔진을 쓸래
    UINT Flags = 0;
    D3D_FEATURE_LEVEL pFeatureLevels[] = { D3D_FEATURE_LEVEL_11_0}; // 지원이 되는지 안되는지 목록 (앞에서부터)
    UINT FeatureLevels = 1; //갯수
    UINT SDKVersion = D3D11_SDK_VERSION;
    hr = D3D11CreateDevice(
        pAdapter,
        DriverType,
        Software,
        Flags,
        pFeatureLevels,
        FeatureLevels,
        SDKVersion,
        &m_pd3dDevice, 
        &pFeatureLevel,
        &m_pImmediateContext);
    if (FAILED(hr))
    {
        return false;
    }

    //IDXGIFactory* m_pGIFactory = nullptr;
    //IDXGISwapChain* m_pSwapChain = nullptr;
    __uuidof(IDXGIFactory); // id 얻기
    hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory);
    if (FAILED(hr)) return false;

    // 후면(백)버퍼 생성 -> 전면버퍼
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1; // 백퍼버 카운트
    sd.BufferDesc.Width = m_rtClient.right;
    sd.BufferDesc.Height = m_rtClient.bottom;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//4바이트 픽셀
    

    sd.BufferDesc.RefreshRate.Numerator = 60; // 새로고침 빈도
    sd.BufferDesc.RefreshRate.Denominator = 1;

    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 출력을 하는 대상
    sd.OutputWindow = m_hWnd;
    sd.Windowed = true; // 윈도우를 쓰겠다.
    //Alt + Enter => 풀스크린 윈도우(모니터 전체를 쓰겠다)

    sd.SampleDesc.Count = 1; //뿌린데 또 뿌리고 퀄리티 향상
    sd.SampleDesc.Quality = 0;
    
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    /*DXGI_MODE_DESC BufferDesc;
    DXGI_SAMPLE_DESC SampleDesc;
    DXGI_USAGE BufferUsage;
    UINT BufferCount;
    HWND OutputWindow;
    BOOL Windowed;
    DXGI_SWAP_EFFECT SwapEffect;
    UINT Flags;*/
    //스왑체인 생성
    m_pGIFactory->CreateSwapChain
    (
        m_pd3dDevice,
        &sd,
        &m_pSwapChain
    );
    if (FAILED(hr))
    {
        return false;
    }

    //만들어진 스왑체인의 0번 버퍼를 가지고 와서
    // 렌더타겟 뷰 생성
    //랜더타겟에 0번버퍼를 사용하겠다.
    ID3D11Texture2D* pBackBuffer = nullptr; // 가로세로의 이미지
    m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRTV);
    pBackBuffer->Release(); //DX에서 Get함수를 호출 시 복사본이 호출이됨

    //뷰포트 설정
    D3D11_VIEWPORT vp;
    vp.Width = m_rtClient.right;
    vp.Height = m_rtClient.bottom;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    m_pImmediateContext->RSSetViewports(1, &vp);

    return true;
}
bool		Sample::Frame()
{
    return true;
}
bool		Sample::Render()
{
    static float fRed = 0.0f;
    fRed += 0.001f;
    m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL); // 백버퍼
    float color[4] = { fRed, 0,0, 1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRTV, color); // 백버퍼
    m_pSwapChain->Present(0, 0); //프론트 버퍼
    return true;
}
bool		Sample::Release()
{
    if (m_pd3dDevice) m_pd3dDevice->Release();
    if (m_pImmediateContext) m_pImmediateContext->Release();
    if (m_pGIFactory) m_pGIFactory->Release();
    if (m_pSwapChain) m_pSwapChain->Release();
    if (m_pRTV) m_pRTV->Release();
    return true;
}

GAME_RUN(P2_CreateWidnow2, 1024, 768)
