#include "Map.h"

bool Map::Build(UINT iWidth, UINT iHeight)
{
    // 전체 셀 개수 = (iWidth-1) * (iHieght-1)
    // 전체 페이스 개수 = (iWidth-1) * (iHiehgt-1) * 2
    // 전체 정점 개수 = iWidth * iHeight
    _dwNumRows = iWidth;
    _dwNumColumns = iHeight;
    _VertexList.resize(iWidth * iHeight);
    int iHalfWidth = iWidth / 2;
    int iHalfHeight = iHeight / 2;
    float fCellDistance = 1.0f;
    for (int iRow = 0; iRow < iHeight; ++iRow)
    {
        for (int iCol = 0; iCol < iWidth; ++iCol)
        {
            _VertexList[iRow * iWidth + iCol].p =
            { (float)(iCol - iHalfWidth) * fCellDistance, cosf(DegreeToRadian(iCol)) * 20.0f + sinf(DegreeToRadian(iRow)) * 20.0f,
                (float)(iHalfHeight - iRow) * fCellDistance };
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
    return true;
}

bool Map::UpdateBuffer(CameraDebug* pMainCamera)
{
    _dwFace = 0;
    DWORD index = 0;
    Vector3D v[3];
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
