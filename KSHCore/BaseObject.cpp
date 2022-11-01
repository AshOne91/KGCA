#include "BaseObject.h"

namespace KDX
{
    ID3D11Buffer* CreateVertexBuffer(ID3D11Device* pd3dDevice, void* pDataAddress, UINT iNumVertex, UINT iVertexSize)
    {
        HRESULT hr;
        ID3D11Buffer* pVB = nullptr;
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.ByteWidth = iVertexSize * iNumVertex; // 바이트 용량
        //GPU 메모리에 할당
        bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.pSysMem = pDataAddress;
        hr = pd3dDevice->CreateBuffer(
            &bd, // 버퍼 할당
            &sd, // 초기 할당된 버퍼를 채우는 CPU메모리 주소
            &pVB);
        return pVB;
    }

    bool BaseObject::Create(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, const std::wstring& shaderName, const std::wstring& textureName)
    {
        _pd3dDevice = pd3dDevice;
        _pImmediateContext = pImmediateContext;
        _szShaderName = shaderName;
        _szTextureName = textureName;
        if (FAILED(CreateConstantBuffer()))
        {
            return false;
        }
        if (FAILED(CreateVertexBuffer()))
        {
            return false;
        }
        if (FAILED(CreateIndexBuffer()))
        {
            return false;
        }
        if (FAILED(CreateShader(shaderName)))
        {
            return false;
        }
        /*if (FAILED(CreateVertexShader(shaderName)))
        {
            return false;
        }
        if (FAILED(CreatePixelShader(shaderName)))
        {
            return false;
        }*/
        if (FAILED(CreateVertexLayout()))
        {
            return false;
        }

        /*_pTexture = I_Tex.Load(textureName);
        if (_pTexture != nullptr)
        {
            _pTextureSRV = _pTexture->_pTextureSRV;
        }*/
        if (LoadTexture(textureName))
        {
            _pTextureSRV = _pTexture->_pTextureSRV;
        }

        if (!Init())
        {
            return false;
        }
        return true;
    }

    void BaseObject::CreateVertexData()
    {
        if (_VertexList.size() > 0)
        {
            _InitVertexList = _VertexList;
            return;
        }

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

        _InitVertexList = _VertexList;
    }

    void BaseObject::CreateIndexData()
    {
        if (_IndexList.size() > 0)
        {
            _dwFace = _IndexList.size() / 3;
            return;
        }
        _IndexList.resize(6);
        _IndexList[0] = 0;
        _IndexList[1] = 1;
        _IndexList[2] = 2;
        _IndexList[3] = 2;
        _IndexList[4] = 1;
        _IndexList[5] = 3;
        /*_IndexList[0] = 1;
        _IndexList[1] = 0;
        _IndexList[2] = 3;
        _IndexList[3] = 3;
        _IndexList[4] = 0;
        _IndexList[5] = 2;*/

        _dwFace = _IndexList.size() / 3;
    }

    void BaseObject::CreateConstantData()
    {
        _cbData.matWorld.Identity();
        _cbData.matView.Identity();
        _cbData.matProj.Identity();
        _cbData.fTimer = 0.0f;
        _cbData.matWorld.Transpose();
        _cbData.matView.Transpose();
        _cbData.matProj.Transpose();
    }

    HRESULT BaseObject::CreateVertexBuffer()
    {
        HRESULT hr;
        CreateVertexData();
        D3D11_BUFFER_DESC       bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.ByteWidth = sizeof(PNCT_VERTEX) * _VertexList.size(); // 바이트 용량
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

    HRESULT BaseObject::CreateConstantBuffer()
    {
        HRESULT hr;
        CreateConstantData();
        D3D11_BUFFER_DESC       bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.ByteWidth = sizeof(VS_CONSTANT_BUFFER) * 1; // 바이트 용량
        // GPU 메모리에 할당
        bd.Usage = D3D11_USAGE_DEFAULT; // 버퍼의 할당 장소 내지는 버퍼용도
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

        D3D11_SUBRESOURCE_DATA  sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.pSysMem = &_cbData;
        hr = _pd3dDevice->CreateBuffer(
            &bd, // 버퍼 할당
            &sd, // 초기 할당된 버퍼를 체우는 CPU메모리 주소
            &_pConstantBuffer);
        return hr;
    }

    HRESULT BaseObject::CreateShader(const std::wstring& filename)
    {
        _pShader = I_Shader.Load(filename);
        if (_pShader != nullptr)
        {
            _pVS = _pShader->_pVS;
            _pPS = _pShader->_pPS;
            _pVSCode = _pShader->_pVSCode;
            _pPSCode = _pShader->_pPSCode;
            return S_OK;
        }
        return E_FAIL;
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
        if (_pVSCode == nullptr)
        {
            return E_FAIL;
        }
        // 정점레이아웃은 정점쉐이더 밀접한 관련.
        // 정점레이아웃 생성시 사전에 정점쉐이더 생성이 필요하다.
        D3D11_INPUT_ELEMENT_DESC ied[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
            { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,24,D3D11_INPUT_PER_VERTEX_DATA, 0},
            { "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0,40,D3D11_INPUT_PER_VERTEX_DATA, 0},
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
        Rotation();

        _pImmediateContext->UpdateSubresource(
            _pVertexBuffer, 0, nullptr,
            &_VertexList.at(0), 0, 0);
    }
    void BaseObject::UpdateConstantBuffer()
    {
        _cbData.matWorld = _matWorld.Transpose();
        _cbData.matView = _matView.Transpose();
        _cbData.matProj = _matProj.Transpose();
        _pImmediateContext->UpdateSubresource(
            _pConstantBuffer, 0, nullptr,
            &_cbData, 0, 0);
    }

    bool BaseObject::LoadTexture(W_STR texturename)
    {
        _pTexture = I_Tex.Load(texturename);
        if (_pTexture != nullptr)
        {
            _pTextureSRV = _pTexture->_pTextureSRV;
            return true;
        }
        return false;
    }

    bool BaseObject::Init()
    {
        return true;
    }

    bool BaseObject::Frame()
    {
        return true;
    }

    bool BaseObject::PreRender()
    {
        //_pTexture->Apply(_pImmediateContext, 0);
        _pImmediateContext->PSSetShaderResources(0, 1, &_pTextureSRV);
        _pImmediateContext->IASetInputLayout(_pVertexLayout);
        _pImmediateContext->VSSetShader(_pVS, NULL, 0);
        _pImmediateContext->PSSetShader(_pPS, NULL, 0);
        UINT stride = sizeof(PNCT_VERTEX); // 정점1개의 바이트용량
        UINT offset = 0; // 정점버퍼에서 출발지점(바이트)
        _pImmediateContext->IASetVertexBuffers(0, 1,
            &_pVertexBuffer, &stride, &offset);
        _pImmediateContext->IASetIndexBuffer(_pIndexBuffer,
            DXGI_FORMAT_R32_UINT, 0);
        //상수버퍼 업데이트
        _pImmediateContext->VSSetConstantBuffers(0, 1, &_pConstantBuffer);
        return true;
    }

    bool BaseObject::Render()
    {
        PreRender();
        PostRender();
        return true;
    }

    bool BaseObject::PostRender()
    {
        if (_pIndexBuffer == nullptr)
            _pImmediateContext->Draw(_VertexList.size(), 0);
        else
            _pImmediateContext->DrawIndexed(_dwFace * 3, 0, 0);
        return true;
    }

    void BaseObject::Rotation()
    {
        Vector3D vCenter;
        vCenter.x = (_VertexList[1].p.x + _VertexList[0].p.x) / 2.0f;
        vCenter.y = (_VertexList[2].p.y + _VertexList[0].p.y) / 2.0f;

        float fDegree = _fAngleDegree;
        float fRadian = DegreeToRadian(fDegree);
        Vector3D vRot;
        for (int vertex = 0; vertex < 4; ++vertex)
        {
            Vector3D vCenterMove = _VertexList[vertex].p - vCenter;
            vRot.x = vCenterMove.x * cos(fRadian) - vCenterMove.y * sin(fRadian);
            vRot.y = vCenterMove.x * sin(fRadian) + vCenterMove.y * cos(fRadian);
            _VertexList[vertex].p = vRot + vCenter;
        }
    }

    bool BaseObject::Release()
    {
        if (_pVertexBuffer) _pVertexBuffer->Release();
        if (_pIndexBuffer) _pIndexBuffer->Release();
        if (_pConstantBuffer) _pConstantBuffer->Release();
        if (_pVertexLayout) _pVertexLayout->Release();
        _pVertexBuffer = nullptr;
        _pIndexBuffer = nullptr;
        _pConstantBuffer = nullptr;
        _pVertexLayout = nullptr;
        return true;
    }

    void BaseObject::SetMatrix(Matrix* matWorld, Matrix* matView, Matrix* matProj)
    {
        if (matWorld != nullptr)
        {
            _matWorld = *matWorld;
        }
        if (matView != nullptr)
        {
            _matView = *matView;
        }
        if (matProj != nullptr)
        {
            _matProj = *matProj;
        }
        UpdateConstantBuffer();
    }
}
