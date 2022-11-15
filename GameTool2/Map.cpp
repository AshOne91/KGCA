#include "pch.h"
#include "Map.h"

float Map::GetHeightmap(int row, int col)
{
    return _VertexList[row * _iNumRows + col].p.y;
}

float Map::GetHeight(float fPosX, float fPosZ)
{
    // fPosX/fPosZ의 위치에 해당하는 높이맵셀을 찾는다.
    // _iNumCols와 _iNumRows은 가로/세로의 실제 크기값임.
    float fCellX = (float)(_iNumCellCols * _fCellDistance / 2.0f + fPosX);
    float fCellZ = (float)(_iNumCellRows * _fCellDistance / 2.0f - fPosZ);

    // 셀의 크기로 나누어 0~1 단위의 값으로 바꾸어 높이맵 배열에 접근한다.
    fCellX /= (float)_fCellDistance;
    fCellZ /= (float)_fCellDistance;

    // fCellx, fCellz 값보다 작거나 같은 최대 정소 (소수부분을 잘라낸다.)
    float fVertexCol = ::floorf(fCellX);
    float fVertexRow = ::floorf(fCellZ);

    // 높이맵 범위를 벗어나면 강제로 초기화 한다.
    if (fVertexCol < 0.0f) fVertexCol = 0.0f;
    if (fVertexRow < 0.0f) fVertexRow = 0.0f;
    if ((float)(_iNumCols - 2) < fVertexCol) fVertexCol = (float)(_iNumCols - 2);
    if ((float)(_iNumRows - 2) < fVertexRow) fVertexRow = (float)(_iNumRows - 2);

    // 계산된 셀의 플랜을 구성하는 4개 정점의 높이값을 찾는다. 
    //  A   B
    //  *---*
    //  | / |
    //  *---*  
    //  C   D
    float A = GetHeightmap((int)fVertexRow, (int)fVertexCol);
    float B = GetHeightmap((int)fVertexRow, (int)fVertexCol + 1);
    float C = GetHeightmap((int)fVertexRow + 1, (int)fVertexCol);
    float D = GetHeightmap((int)fVertexRow + 1, (int)fVertexCol + 1);

    // A정점의 위치에서 떨어진 값(변위값)을 계산한다. 0 ~ 1.0f
    float fDeltaX = fCellX - fVertexCol;
    float fDeltaZ = fCellZ - fVertexRow;
    // 보간작업을 위한 기준 페잇스를 찾는다.
    float fHeight = 0.0f;
    // 윗페이스를 기준으로 보간한다.
    // fDeltaZ + fDeltaX < 1.0f
    if (fDeltaZ < (1.0f - fDeltaX)) //ABC
    {
        float uy = B - A; // A->B
        float vy = C - A; // A->C
                          // 두 정점의 높이값의 차이를 비교하여 델타x의 값에 다라 보간값을 찾는다.
        fHeight = A + Lerp(0.0f, uy, fDeltaX) + Lerp(0.0f, vy, fDeltaZ);
    }
    // 아래페이스를 기준으로 보간한다.
    else // DCB
    {
        float uy = C - D; // D->C
        float vy = B - D; // D->B
                          // 두 정점의 높이값의 차이를 비교하여 델타 z의 값에 따라 보간값을 찾는다.
        fHeight = D + Lerp(0.0f, uy, 1.0f - fDeltaX) + Lerp(0.0f, vy, 1.0f - fDeltaZ);
    }
    return fHeight;
}

float Map::Lerp(float fStart, float fEnd, float fTangent)
{
    return fStart - (fStart * fTangent) + (fEnd * fTangent);
}

bool Map::Build(UINT iWidth, UINT iHeight)
{
    // 전체 셀 개수 = (iWidth-1) * (iHieght-1)
    // 전체 페이스 개수 = (iWidth-1) * (iHiehgt-1) * 2
    // 전체 정점 개수 = iWidth * iHeight
    _iNumRows = iWidth;
    _iNumCols = iHeight;
    _iNumCellCols = _iNumCols - 1;
    _iNumCellRows = _iNumRows - 1;
    _VertexList.resize(iWidth * iHeight);
    int iHalfWidth = iWidth / 2;
    int iHalfHeight = iHeight / 2;
    
    for (int iRow = 0; iRow < iHeight; ++iRow)
    {
        for (int iCol = 0; iCol < iWidth; ++iCol)
        {
            _VertexList[iRow * iWidth + iCol].p =
            { (float)(iCol - iHalfWidth) * _fCellDistance, 
                0.0f,//cosf(DegreeToRadian(iCol))*20.0f+ sinf(DegreeToRadian(iRow)) * 20.0f,
                (float)(iHalfHeight - iRow) * _fCellDistance };
            _VertexList[iRow * iWidth + iCol].p.y = _fHeightList[iRow * _iNumCols + iCol] * _fScaleHeight;
            _VertexList[iRow * iWidth + iCol].c =
            { 1,1,1,1 };
            _VertexList[iRow * iWidth + iCol].t =
            { ((float)iCol / (float)(iWidth - 1)) * 10.0f,
              ((float)iRow / (float)(iHeight - 1)) * 10.0f };
        }
    }

    _IndexList.resize((iWidth - 1) * (iHeight - 1) * 2 * 3.0f);
    UINT iIndex = 0;
    for (int iRow = 0; iRow < iHeight - 1; iRow++)
    {
        for (int iCol = 0; iCol < iWidth - 1; iCol++)
        {
            UINT iNextRow = iRow + 1;
            UINT iNextCol = iCol + 1;
            _IndexList[iIndex + 0] = iRow * iWidth + iCol;
            _IndexList[iIndex + 1] = _IndexList[iIndex + 0] + 1;
            _IndexList[iIndex + 2] = iNextRow * iWidth + iCol;

            _IndexList[iIndex + 3] = _IndexList[iIndex + 2];
            _IndexList[iIndex + 4] = _IndexList[iIndex + 1];
            _IndexList[iIndex + 5] = _IndexList[iIndex + 3] + 1;

            iIndex += 6;
        }
    }
    indexlist.resize(_IndexList.size());
    _dwFace = _IndexList.size() / 3;

    GenVertexNormal();
    return true;
}

bool Map::UpdateBuffer(CameraDebug* pMainCamera)
{
    _dwFace = 0;
    DWORD index = 0;
    TVector3 v[3];
    for (int iFace = 0; iFace < _IndexList.size() / 3; ++iFace)
    {
        UINT i0 = _IndexList[iFace * 3 + 0];
        UINT i1 = _IndexList[iFace * 3 + 1];
        UINT i2 = _IndexList[iFace * 3 + 2];
        v[0] = _VertexList[i0].p;
        v[1] = _VertexList[i1].p;
        v[2] = _VertexList[i2].p;
        for (int i = 0; i < 3; ++i)
        {
            bool bRender = pMainCamera->_vFrustum.ClassifyPoint(v[i]);
            if (bRender)
            {
                indexlist[index++] = i0;
                indexlist[index++] = i1;
                indexlist[index++] = i2;
                _dwFace++;
                break;
            }
        }
    }
    _pImmediateContext->UpdateSubresource(_pIndexBuffer, 0, nullptr, &indexlist.at(0), 0, 0);
    return true;
}

bool Map::LoadHeightMap(ID3D11Device* pd3dDevice, // 디바이스 객체
    ID3D11DeviceContext* pContext, W_STR loadTexture)
{
    ComPtr<ID3D11Resource> pTexture;
    HRESULT hr = DirectX::CreateWICTextureFromFileEx(pd3dDevice, loadTexture.c_str(),
        0, D3D11_USAGE_STAGING, 0,
        D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE, 0,
        WIC_LOADER_DEFAULT,
        pTexture.GetAddressOf(), nullptr);

    ID3D11Texture2D* pTexture2D = NULL;
    if (FAILED(pTexture->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&pTexture2D)))
    {
        return false;
    }

    D3D11_TEXTURE2D_DESC td;
    pTexture2D->GetDesc(&td);

    _fHeightList.resize(td.Height * td.Width);

    D3D11_MAPPED_SUBRESOURCE MappedFaceDest;
    if (SUCCEEDED(pContext->Map(pTexture2D, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, 0,
        &MappedFaceDest)))
    {
        UCHAR* pTexels = (UCHAR*)MappedFaceDest.pData;
        for (UINT row = 0; row < td.Height; row++)
        {
            UINT rowStart = row * MappedFaceDest.RowPitch;
            for (UINT col = 0; col < td.Width; ++col)
            {
                UINT colStart = col * 4;
                UINT uRed = pTexels[rowStart + colStart + 0];
                _fHeightList[row * td.Width + col] = (float)uRed / 255.0f;
            }
        }
        pContext->Unmap(pTexture2D, D3D11CalcSubresource(0, 0, 1));
    }

    _iNumRows = td.Height;
    _iNumCols = td.Width;
    pTexture2D->Release();
    return true;
}

void Map::GenVertexNormal()
{
    std::vector<TVector3> _FaceNormals;
    _FaceNormals.resize(_dwFace);
    UINT iFace = 0;
    for (UINT i = 0; i < _IndexList.size(); i += 3)
    {
        UINT i0 = _IndexList[i + 0];
        UINT i1 = _IndexList[i + 1];
        UINT i2 = _IndexList[i + 2];
        _FaceNormals[iFace++] = ComputeFaceNormal(i0, i1, i2);
    }
    struct tVertexInfo
    {
        std::vector<UINT> faceIndexArray;
        TVector3 vNormal;
    };
    std::vector<tVertexInfo> _VertexInfo;
    _VertexInfo.resize(_iNumCols* _iNumRows);
    for (UINT iFace = 0; iFace < _dwFace; ++iFace)
    {
        for (UINT i = 0; i < 3; ++i)
        {
            UINT i0 = _IndexList[iFace * 3 + i];
            _VertexInfo[i0].faceIndexArray.push_back(iFace);
        }
    }
    for (UINT iVertex = 0; iVertex < _VertexInfo.size(); ++iVertex)
    {
        for (UINT i = 0; i < _VertexInfo[iVertex].faceIndexArray.size(); ++i)
        {
            _VertexInfo[iVertex].vNormal +=
                _FaceNormals[_VertexInfo[iVertex].faceIndexArray[i]];
        }
        D3DXVec3Normalize(&_VertexInfo[iVertex].vNormal,
            &_VertexInfo[iVertex].vNormal);

        _VertexList[iVertex].n = _VertexInfo[iVertex].vNormal;
#ifdef _DEBUG
        TVector3 vLight = { 0, 1, 0 };
        float fDot = D3DXVec3Dot(&vLight, &_VertexList[iVertex].n);
        _VertexList[iVertex].c = { fDot, fDot, fDot, 1 };
#endif
    }
}

TVector3 Map::ComputeFaceNormal(UINT i0, UINT i1, UINT i2)
{
    TVector3 vNormal;
    TVector3 e0 = _VertexList[i1].p - _VertexList[i0].p;
    TVector3 e1 = _VertexList[i2].p - _VertexList[i0].p;
    D3DXVec3Cross(&vNormal, &e0, &e1);
    D3DXVec3Normalize(&vNormal, &vNormal);
    return vNormal;
}
