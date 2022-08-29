#include "Sample.h"
HRESULT Sample::CreateVertexBuffer()
{
    HRESULT hr;
    // NDC(Nomalize Divice Coordinate)
    // NDC ��ǥ�� ����
    // x -> -1 ~ +1
    // y -> -1 ~ +1
    // z -> 0 ~ 1
    // +1 v0           v1
    // -1        0.0   +1
    // -1 v2
    SimpleVertex vertices[] =
    {
        //�ݵ�� �ð����(�ո�)���� �����Ѵ�. // 3d�� �ո� �޸��� �ִ�.
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
    bd.ByteWidth = sizeof(SimpleVertex) * NumVertex;//����Ʈ �뷮
    // GPU �޸𸮿� �Ҵ�
    bd.Usage = D3D11_USAGE_DEFAULT; //������ �Ҵ� ��� ������ ���ۿ뵵
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
        &bd, // ���� �Ҵ�
        &sd, // �ʱ� �Ҵ�� ���۸� ü��� CPU�޸� �ּ�(����� ������ ���ÿ� CPU�޸𸮸� GPU�޸𸮿� ����)
        &m_pVertexBuffer);

    return hr;
}
HRESULT Sample::CreateShader()
{
    HRESULT hr;
    // �������̴� ������
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
    // �������̾ƿ��� �������̴� ������ ����,
    // �������̾ƿ� ������ ������ �������̴� ������ �ʿ��ϴ�.
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
    // �ﰢ�� ������
    UINT stride = sizeof(SimpleVertex); // ���� 1���� ����Ʈ �뷮
    UINT offset = 0; // �������ۿ��� �������(����Ʈ)
    //SLOT(�������͸�)
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
