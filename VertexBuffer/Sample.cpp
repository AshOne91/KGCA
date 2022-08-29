#include "Sample.h"
HRESULT Sample::CreateVertexBuffer()
{
    HRESULT hr;
    // NDC(Nomalize Divice Coordinate)
    // NDC 좌표계 공간
    // x -> -1 ~ +1
    // y -> -1 ~ +1
    // z -> 0 ~ 1
    // +1 v0           v1
    // -1        0.0   +1
    // -1 v2
    SimpleVertex vertices[] =
    {
        //반드시 시계방향(앞면)으로 구성한다. // 3d는 앞면 뒷면이 있다.
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// v0
        +0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // v1
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // v2

        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// v0
        +0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // v1
        +0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // v2
    };
    UINT NumVertex = sizeof(vertices) / sizeof(vertices[0]);
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(SimpleVertex) * NumVertex;//바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; //버퍼의 할당 장소 내지는 버퍼용도
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    /*bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    bd.StructureByteStride = 0;*/
    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = vertices;
    /*UINT SysMemPitch;
    UINT SysMemSlicePitch;*/
    hr = m_pd3dDevice->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소(현재는 생성과 동시에 CPU메모리를 GPU메모리에 복사)
        &m_pVertexBuffer);

    return hr;
}
HRESULT Sample::CreateShader()
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
        &pErrorCode
    );
    if (FAILED(hr))
    {
        if (pErrorCode != nullptr)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }
    m_pd3dDevice->CreateVertexShader(
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        0,
        &m_pVertexShader
    );

    pErrorCode = nullptr;
    hr = D3DCompileFromFile(
        L"PixelShader.txt",
        NULL,
        NULL,
        "PSMain",
        "ps_5_0",
        0,
        0,
        &m_pPSCode,
        &pErrorCode
    );
    if (FAILED(hr))
    {
        if (pErrorCode != nullptr)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }
    hr = m_pd3dDevice->CreatePixelShader(
        m_pPSCode->GetBufferPointer(),
        m_pPSCode->GetBufferSize(),
        0,
        &m_pPixelShader
    );
    return hr;
}
HRESULT Sample::CreateVertexLayout()
{
    HRESULT hr;
    // 정점레이아웃은 정점쉐이더 밀접한 관련,
    // 정점레이아웃 생성시 사전에 정점쉐이더 생성이 필요하다.
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    //ZeroMemory(&ied, sizeof(D3D11_INPUT_ELEMENT_DESC));
    /*ied.SemanticName = "POSITION";
    ied.SemanticIndex = 0;
    ied.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    ied.InputSlot = 0;
    ied.AlignedByteOffset = 0;
    ied.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    ied.InstanceDataStepRate = 0;*/

    UINT NumElemnets = sizeof(ied) / sizeof(ied[0]);
    hr = m_pd3dDevice->CreateInputLayout(
        ied,
        NumElemnets,
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        &m_pVertexLayout);
    return hr;
}

bool		Sample::Init()
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
bool		Sample::Frame()
{
    return true;
}
bool		Sample::Render()
{
    // 삼각형 렌더링
    UINT stride = sizeof(SimpleVertex); // 정점 1개의 바이트 용량
    UINT offset = 0; // 정점버퍼에서 출발지점(바이트)
    //SLOT(레지스터리)
    m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
    m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);
    m_pImmediateContext->HSSetShader(NULL, NULL, 0);
    m_pImmediateContext->DSSetShader(NULL, NULL, 0);
    m_pImmediateContext->GSSetShader(NULL, NULL, 0);
    m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);
    m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pImmediateContext->Draw(6, 0);
    return true;
}
bool		Sample::Release()
{
    if (m_pVertexBuffer) m_pVertexBuffer->Release();
    if (m_pVertexLayout) m_pVertexLayout->Release();
    if (m_pVertexShader) m_pVertexShader->Release();
    if (m_pPixelShader) m_pPixelShader->Release();
    if (m_pVSCode) m_pVSCode->Release();
    if (m_pPSCode) m_pPSCode->Release();
    return true;
}


GAME_RUN(P2_CreateDevice_0, 1024, 768)
