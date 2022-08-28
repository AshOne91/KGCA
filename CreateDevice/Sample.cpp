#include "Sample.h"
bool		Sample::Init()
{
    HRESULT hr;
    D3D_FEATURE_LEVEL pFeatureLevel; // � ������ ���� Ȯ�ΰ���
    IDXGIAdapter* pAdapter = nullptr; // �׷��� ī��(�׷���ī�� ��ȸ ����)
    D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE; //�ϵ���� ����(�׷���ī���� ����) �ϵ���� ����(GPU), ����Ʈ����(CPU)
    HMODULE Software = NULL;//�ٸ� ������ ������ ����
    UINT Flags = 0;
    D3D_FEATURE_LEVEL pFeatureLevels[] = { D3D_FEATURE_LEVEL_11_0}; // ������ �Ǵ��� �ȵǴ��� ��� (�տ�������)
    UINT FeatureLevels = 1; //����
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
    __uuidof(IDXGIFactory); // id ���
    hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory);
    if (FAILED(hr)) return false;

    // �ĸ�(��)���� ���� -> �������
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1; // ���۹� ī��Ʈ
    sd.BufferDesc.Width = m_rtClient.right;
    sd.BufferDesc.Height = m_rtClient.bottom;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//4����Ʈ �ȼ�
    

    sd.BufferDesc.RefreshRate.Numerator = 60; // ���ΰ�ħ ��
    sd.BufferDesc.RefreshRate.Denominator = 1;

    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ����� �ϴ� ���
    sd.OutputWindow = m_hWnd;
    sd.Windowed = true; // �����츦 ���ڴ�.
    //Alt + Enter => Ǯ��ũ�� ������(����� ��ü�� ���ڴ�)

    sd.SampleDesc.Count = 1; //�Ѹ��� �� �Ѹ��� ����Ƽ ���
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
    //����ü�� ����
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

    //������� ����ü���� 0�� ���۸� ������ �ͼ�
    // ����Ÿ�� �� ����
    //����Ÿ�ٿ� 0�����۸� ����ϰڴ�.
    ID3D11Texture2D* pBackBuffer = nullptr; // ���μ����� �̹���
    m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRTV);
    pBackBuffer->Release(); //DX���� Get�Լ��� ȣ�� �� ���纻�� ȣ���̵�

    //����Ʈ ����
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
    m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, NULL); // �����
    float color[4] = { fRed, 0,0, 1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRTV, color); // �����
    m_pSwapChain->Present(0, 0); //����Ʈ ����
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
