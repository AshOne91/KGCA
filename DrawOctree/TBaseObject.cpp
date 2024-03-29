#include "TBaseObject.h"
void TBaseObject::SetDevice(
            ID3D11Device* pd3dDevice,
            ID3D11DeviceContext* pContext)
{
    m_pd3dDevice        = pd3dDevice;
    m_pImmediateContext = pContext;
}
HRESULT TBaseObject::CreateVertexBuffer()
{
    HRESULT hr;
    // NDC 좌표계 공간
    // x -> -1 ~ +1
    // y -> -1 ~ +1
    // z -> 0 ~  +1
    // +1 V0--------v1
    //           /
    // -1      0,0     +1
    //       /
    // -1 v2
    // float  0  ~ 7
    // pos    0 ~ 3,  0~ 11
    // color  4 ~ 7   12~
    m_VertexList.resize(6);
    m_VertexList[0].p = { -1.0f, 1.0f, 0.0f };
    m_VertexList[0].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    m_VertexList[1].p = { +1.0f, 1.0f,  0.0f };
    m_VertexList[1].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    m_VertexList[2].p = { -1.0f, -1.0f, 0.0f };
    m_VertexList[2].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    m_VertexList[3].p = { -1.0f, -1.0f, 0.0f };
    m_VertexList[3].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    m_VertexList[4].p = { +1.0f, 1.0f,  0.0f };
    m_VertexList[4].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    m_VertexList[5].p = { +1.0f, -1.0f, 0.0f };
    m_VertexList[5].c = { 1.0f, 0.0f, 0.0f, 0.0f };   
    UINT NumVertex = m_VertexList.size();
    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(SimpleVertex) * NumVertex; // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &m_VertexList.at(0);
    hr = m_pd3dDevice->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
        &m_pVertexBuffer);
    return hr;
}
HRESULT TBaseObject::CreateShader()
{
    HRESULT hr;
    // 정점쉐이더 컴파일 
    ID3DBlob* pErrorCode = nullptr;
    hr = D3DCompileFromFile(
        L"VertexShader.txt",
        NULL,
        NULL,
        "main",
        "vs_5_0",
        0,
        0,
        &m_pVSCode,
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
    hr = m_pd3dDevice->CreateVertexShader(
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        NULL,
        &m_pVS);

    // 픽쉘쉐이더 컴파일  
    hr = D3DCompileFromFile(
        L"PixelShader.txt",
        NULL,
        NULL,
        "PSMain",
        "ps_5_0",
        0,
        0,
        &m_pPSCode,
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
    hr = m_pd3dDevice->CreatePixelShader(
        m_pPSCode->GetBufferPointer(),
        m_pPSCode->GetBufferSize(),
        NULL,
        &m_pPS);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }
    return hr;
}
HRESULT TBaseObject::CreateVertexLayout()
{
    HRESULT hr;
    // 정점레이아웃은 정점쉐이더 밀접한 관련.
    // 정점레이아웃 생성시 사전에 정점쉐이더 생성이 필요하다.
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,12,D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    UINT NumElements = sizeof(ied) / sizeof(ied[0]);
    hr = m_pd3dDevice->CreateInputLayout(
        ied,
        NumElements,
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        &m_pVertexLayout);
    return hr;
}
bool	TBaseObject::Init()
{
    if (FAILED(CreateVertexBuffer()))
    {
        return false;
    }
    if (FAILED(CreateShader()))
    {
        return false;
    }
    if (FAILED(CreateVertexLayout()))
    {
        return false;
    }
    return true;
}
bool	TBaseObject::Frame()
{
    m_VertexList[0].p = { -1.0f, 1.0f, 0.0f };
    m_VertexList[0].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    // gpu update
    m_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, 0, NULL,
        &m_VertexList.at(0), 0, 0 );
    return true;
}
bool	TBaseObject::Render()
{
    // 삼각형 랜더링
    UINT stride = sizeof(SimpleVertex); // 정점1개의 바이트용량
    UINT offset = 0; // 정점버퍼에서 출발지점(바이트)
    //SLOT(레지스터리)
    m_pImmediateContext->IASetVertexBuffers(0, 1,
        &m_pVertexBuffer, &stride, &offset);
    m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    m_pImmediateContext->VSSetShader(m_pVS, NULL, 0);
    m_pImmediateContext->PSSetShader(m_pPS, NULL, 0);

    m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pImmediateContext->Draw(m_VertexList.size(), 0);
    return true;
}
bool	TBaseObject::Release()
{
    if (m_pVertexBuffer) m_pVertexBuffer->Release();
    if (m_pVertexLayout) m_pVertexLayout->Release();
    if (m_pVS) m_pVS->Release();
    if (m_pPS) m_pPS->Release();
    if (m_pVSCode) m_pVSCode->Release();
    if (m_pPSCode) m_pPSCode->Release();
    return true;
}
