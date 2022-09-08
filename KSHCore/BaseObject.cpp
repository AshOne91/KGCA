#include "BaseObject.h"

bool BaseObject::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, const std::wstring& shaderName, const std::wstring& textureName)
{
    _pd3dDevice = pd3dDevice;
    _pImmediateContext = pImmediateContext;
    if (FAILED(CreateVertexBuffer()))
    {
        return false;
    }
    if (FAILED(CreateIndexBuffer()))
    {
        return false;
    }
    if (FAILED(CreateVertexShader(shaderName)))
    {
        return false;
    }
    if (FAILED(CreatePixelShader(shaderName)))
    {
        return false;
    }
    if (FAILED(CreateVertexLayout()))
    {
        return false;
    }

    _pTexture = I_Tex.Load(textureName);
	return true;
}

void BaseObject::CreateVertexData()
{
    _VertexList.resize(4);
    _VertexList[0].p = { -1.0f, 1.0f, 0.0f };
    _VertexList[1].p = { +1.0f, 1.0f,  0.0f };
    _VertexList[2].p = { -1.0f, -1.0f, 0.0f };
    _VertexList[3].p = { 1.0f, -1.0f, 0.0f };

    _VertexList[0].c = { 1.0f, 1.0f, 1.0f, 1.0f };
    _VertexList[1].c = { 1.0f, 1.0f, 1.0f, 1.0f };
    _VertexList[2].c = { 1.0f, 1.0f, 1.0f, 1.0f };
    _VertexList[3].c = { 1.0f, 1.0f, 1.0f, 1.0f };

    _VertexList[0].t = { 0.0f, 0.0f };
    _VertexList[1].t = { 1.0f, 0.0f };
    _VertexList[2].t = { 0.0f, 1.0f };
    _VertexList[3].t = { 1.0f, 1.0f };
}

void BaseObject::CreateIndexData()
{
    _IndexList.resize(6);
    _IndexList[0] = 0;
    _IndexList[1] = 1;
    _IndexList[2] = 2;
    _IndexList[3] = 2;
    _IndexList[4] = 1;
    _IndexList[5] = 3;
}

HRESULT BaseObject::CreateVertexBuffer()
{
    HRESULT hr;
    CreateVertexData();
    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(SimpleVertex) * _VertexList.size(); // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &_VertexList.at(0);
    hr = _pd3dDevice->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
        &_pVertexBuffer);
    return hr;
}

HRESULT BaseObject::CreateIndexBuffer()
{
    HRESULT hr;

    CreateIndexData();

    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(DWORD) * _IndexList.size(); // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &_IndexList.at(0);
    hr = _pd3dDevice->CreateBuffer(
        &bd, // 버퍼 할당
        &sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
        &_pIndexBuffer);
    return hr;
}

HRESULT BaseObject::CreateVertexShader(const std::wstring& filename)
{
    HRESULT hr;
    // 정점쉐이더 컴파일 
    ID3DBlob* pErrorCode = nullptr;
    hr = D3DCompileFromFile(
        filename.c_str(),
        NULL,
        NULL,
        "VS",
        "vs_5_0",
        0,
        0,
        &_pVSCode,
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
    hr = _pd3dDevice->CreateVertexShader(
        _pVSCode->GetBufferPointer(),
        _pVSCode->GetBufferSize(),
        NULL,
        &_pVS);
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

HRESULT BaseObject::CreatePixelShader(const std::wstring& filename)
{
    HRESULT hr;
    ID3DBlob* pErrorCode = nullptr;
    // 픽쉘쉐이더 컴파일  
    hr = D3DCompileFromFile(
        filename.c_str(),
        NULL,
        NULL,
        "PS",
        "ps_5_0",
        0,
        0,
        &_pPSCode,
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
    hr = _pd3dDevice->CreatePixelShader(
        _pPSCode->GetBufferPointer(),
        _pPSCode->GetBufferSize(),
        NULL,
        &_pPS);
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

HRESULT BaseObject::CreateVertexLayout()
{
    HRESULT hr;
    // 정점레이아웃은 정점쉐이더 밀접한 관련.
    // 정점레이아웃 생성시 사전에 정점쉐이더 생성이 필요하다.
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,12,D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0,28,D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    UINT NumElements = sizeof(ied) / sizeof(ied[0]);
    hr = _pd3dDevice->CreateInputLayout(
        ied,
        NumElements,
        _pVSCode->GetBufferPointer(),
        _pVSCode->GetBufferSize(),
        &_pVertexLayout);

    return hr;
}

void BaseObject::UpdateVertexBuffer()
{
    _pImmediateContext->UpdateSubresource(
        _pVertexBuffer, 0, nullptr,
        &_VertexList.at(0), 0, 0);
}

bool BaseObject::Init()
{
    return true;
}

bool BaseObject::Frame()
{
    return true;
}

bool BaseObject::Render()
{
    _pTexture->Apply(_pImmediateContext, 0);
    _pImmediateContext->IASetInputLayout(_pVertexLayout);
    _pImmediateContext->VSSetShader(_pVS, NULL, 0);
    _pImmediateContext->PSSetShader(_pPS, NULL, 0);
    UINT stride = sizeof(SimpleVertex); // 정점1개의 바이트용량
    UINT offset = 0; // 정점버퍼에서 출발지점(바이트)
    _pImmediateContext->IASetVertexBuffers(0, 1,
        &_pVertexBuffer, &stride, &offset);
    _pImmediateContext->IASetIndexBuffer(_pIndexBuffer,
        DXGI_FORMAT_R32_UINT, 0);
    if (_pIndexBuffer == nullptr)
        _pImmediateContext->Draw(_VertexList.size(), 0);
    else
        _pImmediateContext->DrawIndexed(_IndexList.size(), 0, 0);
    return true;
}

bool BaseObject::Release()
{
    if (_pVertexBuffer) _pVertexBuffer->Release();
    if (_pIndexBuffer) _pIndexBuffer->Release();
    if (_pVertexLayout) _pVertexLayout->Release();
    if (_pVS) _pVS->Release();
    if (_pPS) _pPS->Release();
    if (_pVSCode) _pVSCode->Release();
    if (_pPSCode) _pPSCode->Release();
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _pVertexLayout = nullptr;
    _pVS = nullptr;
    _pPS = nullptr;
    _pVSCode = nullptr;
    _pPSCode = nullptr;
    return true;
}
