#include "BaseObject.h"
#include "TextureManager.h"
#include "ShaderManager.h"

void BaseObject::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
    _pd3dDevice = pd3dDevice;
    _pImmediateContext = pContext;
}

HRESULT BaseObject::CreateVertexBuffer()
{
    HRESULT hr;
    // NDC 좌표계 공간
    // x -> -1 ~ +1
    // y -> -1 ~ +1
    // z -> 0 ~  +1
    // +1 V0--------v1,v4
    //           /
    // -1      0,0     +1
    //       /-+
    // -1 v2,v3        v5
    // float  0  ~ 7
    // pos    0 ~ 3,  0~ 11
    // color  4 ~ 7   12~


    // 정점버퍼를 만들어 DirectX 랜더링 파이프라인으로 보내서 사용
    // x, y -> -1 ~ +1
    // z -> 0 ~ +1
    //
    _vertexList.resize(6);
    _vertexList[0].p = { -1.0f, 1.0f, 0.0f };
    _vertexList[0].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    _vertexList[0].t = { 0.0f, 0.0f };
    _vertexList[1].p = { +1.0f, 1.0f,  0.0f };
    _vertexList[1].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    _vertexList[1].t = { 1.0f, 0.0f };
    _vertexList[2].p = { -1.0f, -1.0f, 0.0f };
    _vertexList[2].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    _vertexList[2].t = { 0.0f, 1.0f };
    _vertexList[3].p = { -1.0f, -1.0f, 0.0f };
    _vertexList[3].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    _vertexList[3].t = { 0.0f, 1.0f };
    _vertexList[4].p = { +1.0f, 1.0f,  0.0f };
    _vertexList[4].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    _vertexList[4].t = { 1.0f, 0.0f };
    _vertexList[5].p = { +1.0f, -1.0f, 0.0f };
    _vertexList[5].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    _vertexList[5].t = { 1.0f, 1.0f };

    //typedef struct D3D11_BUFFER_DESC
    //{
    //    UINT ByteWidth; 생성되는 버퍼 크기
    //    D3D11_USAGE Usage; // 생성되는 버퍼의 읽기 및 쓰기 방법을 지정한다.
    //    UINT BindFlags; // 버퍼가 파이프라인에 바인딩하는 방법을 지정
    //    UINT CPUAccessFlags; //CPU가 생성되는 버퍼에 접근하는 유형을 지정한다.
    //    UINT MiscFlags; // 추가적인 옵션 플래
    //    UINT StructureByteStride; // 구조화된 버퍼를 사용할 경우에 구조체 버퍼의 크기(바이트 크기)
    //} 	D3D11_BUFFER_DESC;


    // ByteWidth 버퍼의 전체 크기를 지정하는 것
    // BindFlags 버퍼가 어떤 종류의 버퍼 인지 지정하는 것
    // CPUAccessFlags CPU 리소스 읽기 및 쓰기를 할 필요가 없다는 것
    // MiscFlags 추가적 옵션을 설정하는 것
    // 
    // D3D11_SUBRESOURCE_DATA
    // pSysMem 초기화 데이터에 대한 포인터
    // SysMemPitch 텍스처 리소스 한줄의 크기(기본값 사용)
    //
    UINT NumVertex = _vertexList.size();
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(SimpleVertex) * NumVertex; // 바이트 용량
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &_vertexList.at(0);
    hr = _pd3dDevice->CreateBuffer(&bd, &sd, &_pVertexBuffer);
    return hr;
}

bool BaseObject::CreateShader(std::wstring filename)
{
    _pShader = I_Shader.Load(filename);

    if (_pShader == nullptr)
    {
        return false;
    }
    return true;
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
        _pShader->_pVSCode->GetBufferPointer(),
        _pShader->_pVSCode->GetBufferSize(),
        &_pVertexLayout);
    return hr;
}

bool BaseObject::LoadTexture(std::wstring filename)
{
    HRESULT hr;
    _pTexture = I_Tex.Load(filename);
    if (_pTexture == nullptr)
    {
        return false;
    }

    return true;
}

bool BaseObject::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext, const std::wstring& textName, const std::wstring& shaderName)
{
    SetDevice(pd3dDevice, pContext);
    if (FAILED(CreateVertexBuffer()))
    {
        return false;
    }
    if (FAILED(CreateShader(shaderName)))
    {
        return false;
    }
    if (FAILED(CreateVertexLayout()))
    {
        return false;
    }
    if (FAILED(LoadTexture(textName)))
    {
        return false;
    }
    return true;
}

bool BaseObject::Init()
{
    return true;
}

bool BaseObject::Frame()
{
    _vertexList[0].p = { -1.0f, 1.0f, 0.0f };
    _vertexList[0].c = { 1.0f, 0.0f, 0.0f, 0.0f };
    // gpu update
    _pImmediateContext->UpdateSubresource(
        _pVertexBuffer, 0, NULL,
        &_vertexList.at(0), 0, 0);
    return true;
}

bool BaseObject::Render()
{
    // 삼각형 랜더링
    UINT stride = sizeof(SimpleVertex); // 정점1개의 바이트용량
    UINT offset = 0; // 정점버퍼에서 출발지점(바이트)
    //SLOT(레지스터리)

    // 생성된 정점버퍼를 바인딩
    _pImmediateContext->IASetVertexBuffers(0, 1,
        &_pVertexBuffer, &stride, &offset);
    // 정점 레이아웃 바인딩(IA_Stage에 바인딩 해야함)
    _pImmediateContext->IASetInputLayout(_pVertexLayout);

    //쉐이더 바인딩
    _pImmediateContext->VSSetShader(_pShader->_pVS, NULL, 0);
    _pImmediateContext->PSSetShader(_pShader->_pPS, NULL, 0);

    _pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    // tex
    _pImmediateContext->PSSetShaderResources(0, 1,
        &_pTexture->_pTextureSRV);

    //정점버퍼 개수, 시작 위치
    _pImmediateContext->Draw(_vertexList.size(), 0);
    return true;
}

bool BaseObject::Release()
{
    _pTexture->Release();
    if (_pVertexBuffer) _pVertexBuffer->Release();
    if (_pVertexLayout) _pVertexLayout->Release();
    _pShader->Release();
    return true;
}
