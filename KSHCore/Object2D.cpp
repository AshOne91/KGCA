#include "Object2D.h"

bool Object2D::Frame()
{
    return true;
}

void Object2D::SetRect(const Rect& rt)
{
    _rtInit = rt;
    //텍스쳐 크기
    _ptImageSize.x = _pTexture->_Desc.Width;
    _ptImageSize.y = _pTexture->_Desc.Height;

    //전체 텍스쳐 크기에서 0~1사이의 값 셋팅(얻어올 텍스쳐 스프라이트의 좌표)
    // 90 -> 0 ~ 1
    _rtUV.x1 = rt.x1 / _ptImageSize.x; // u
    _rtUV.y1 = rt.y1 / _ptImageSize.y; // v
    _rtUV.w = rt.w / _ptImageSize.x;
    _rtUV.h = rt.h / _ptImageSize.y;
}

// 화면 좌표 -> NDC(Noramlize Device Coordinate)이며, 이 공간은 투영(Projection) 행렬에 정의
void Object2D::SetPosition(const Vector2D& vPos)
{
    _vPos = vPos;
    // 0 ~ 800 -> 0~1 -> -1 ~ + 1
    _vDrawPos.x = (vPos.x / g_rtClient.right) * 2.0f - 1.0f;
    _vDrawPos.y = -((vPos.y / g_rtClient.bottom) * 2.0f - 1.0f);
    _vDrawSize.x = (_rtInit.w / g_rtClient.right) * 2.0f;
    _vDrawSize.y = (_rtInit.h / g_rtClient.bottom) * 2.0f;

    UpdateVertexBuffer();
}

void Object2D::SetDirection(const Vector2D& vDir)
{
    _vDir = vDir;
}

void Object2D::UpdateVertexBuffer()
{
    _VertexList[0].p = { _vDrawPos.x, _vDrawPos.y, 0.0f };
    _VertexList[0].t = { _rtUV.x1, _rtUV.y1 };

    _VertexList[1].p = { _vDrawPos.x + _vDrawSize.x, _vDrawPos.y,  0.0f };
    _VertexList[1].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 };

    _VertexList[2].p = { _vDrawPos.x, _vDrawPos.y - _vDrawSize.y, 0.0f };
    _VertexList[2].t = { _rtUV.x1, _rtUV.y1 + _rtUV.h };

    /*_VertexList[3].p = _VertexList[2].p;
    _VertexList[3].t = _VertexList[2].t;

    _VertexList[4].p = _VertexList[1].p;
    _VertexList[4].t = _VertexList[1].t;

    _VertexList[5].p = { _vDrawPos.x + _vDrawSize.x, _vDrawPos.y - _vDrawSize.y, 0.0f };
    _VertexList[5].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 + _rtUV.h };*/ //인덱스 버퍼 사용으로 주석처리

    _VertexList[3].p = { _vDrawPos.x + _vDrawSize.x, _vDrawPos.y - _vDrawSize.y, 0.0f };
    _VertexList[3].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 + _rtUV.h };

    _pImmediateContext->UpdateSubresource(_pVertexBuffer, 0, NULL, &_VertexList.at(0), 0, 0);
}

void Object2D::SetMask(Texture* pMaskTex)
{
    _pMaskTex = pMaskTex;
}