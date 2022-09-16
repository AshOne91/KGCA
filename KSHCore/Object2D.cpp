#include "Object2D.h"

Vector2D Func(float radian, Vector2D test, float posX, float posY)
{
    test.x -= posX;
    test.y -= posY;

    float Sin = sinf(radian);
    float Cos = cosf(radian);


    float tempX = (Cos * test.x) + (-Sin * test.y) + posX;
    float tempY = (Sin * test.x) + (Cos * test.y) + posY;

    test.x = tempX;
    test.y = tempY;

    return test;
}

void Object2D::SetCameraPos(const Vector2D& vCamera)
{
    _vCameraPos = vCamera;
}

void Object2D::SetCameraSize(const Vector2D& vSize)
{
    _vViewSize = vSize;
}

void Object2D::ScreenToNDC()
{
    // 0  ~ 800   -> 0~1 ->  -1 ~ +1
    _vDrawPos.x = (_vPos.x / g_rtClient.right) * 2.0f - 1.0f;
    _vDrawPos.y = -((_vPos.y / g_rtClient.bottom) * 2.0f - 1.0f);
    _vDrawSize.x = (_rtInit.w / g_rtClient.right) * 2.0f;
    _vDrawSize.y = (_rtInit.h / g_rtClient.bottom) * 2.0f;
}

// 월드좌표 -> 뷰 좌표 -> NDC 좌표
void Object2D::ScreenToCamera(const Vector2D& vCameraPos, const Vector2D& vViewPort)
{
    Vector2D vPos = _vPos;
    vPos.x = vPos.x - vCameraPos.x;
    vPos.y = vPos.y - vCameraPos.y;

    // 0  ~ 800   -> 0~1 ->  -1 ~ +1
    _vDrawPos.x = vPos.x * (2.0f / vViewPort.x);
    _vDrawPos.y = vPos.y * (2.0f / vViewPort.y) * -1.0f;

    _vDrawSize.x = (_rtInit.w / vViewPort.x) * 2;
    _vDrawSize.y = (_rtInit.h / vViewPort.y) * 2;
}

void Object2D::SetPosition(const Vector2D& vPos, const Vector2D& vCamera)
{
    _vPos = vPos;
    ScreenToCamera(vCamera, _vViewSize);
    UpdateVertexBuffer();
}

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
    ScreenToNDC();
    UpdateVertexBuffer();
}

void Object2D::SetDirection(const Vector2D& vDir)
{
    _vDir = vDir;
}

void Object2D::UpdateVertexBuffer()
{
    float radian = g_fGameTimer * 0.1f;
    Vector2D test = Func(radian, Vector2D(_vDrawPos.x, _vDrawPos.y), _vDrawPos.x, _vDrawPos.y);
    _VertexList[0].p = { test.x, test.y, 0.0f };
    _VertexList[0].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 }; // uv반전 구현
    //_VertexList[0].t = { _rtUV.x1, _rtUV.y1 }; 

    test = Func(radian, Vector2D(_vDrawPos.x + _vDrawSize.x, _vDrawPos.y), _vDrawPos.x, _vDrawPos.y);
    _VertexList[1].p = { test.x, test.y,  0.0f };
    _VertexList[1].t = { _rtUV.x1, _rtUV.y1 }; // uv반전 구현
    //_VertexList[1].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 };


    test = Func(radian, Vector2D(_vDrawPos.x, _vDrawPos.y - _vDrawSize.y), _vDrawPos.x, _vDrawPos.y);
    _VertexList[2].p = { test.x, test.y, 0.0f };
    _VertexList[2].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 + _rtUV.h }; // uv반전 구현
    //_VertexList[2].t = { _rtUV.x1, _rtUV.y1 + _rtUV.h };

    /*_VertexList[3].p = _VertexList[2].p;
    _VertexList[3].t = _VertexList[2].t;

    _VertexList[4].p = _VertexList[1].p;
    _VertexList[4].t = _VertexList[1].t;

    _VertexList[5].p = { _vDrawPos.x + _vDrawSize.x, _vDrawPos.y - _vDrawSize.y, 0.0f };
    _VertexList[5].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 + _rtUV.h };*/ //인덱스 버퍼 사용으로 주석처리

    test = Func(radian, Vector2D(_vDrawPos.x + _vDrawSize.x, _vDrawPos.y - _vDrawSize.y), _vDrawPos.x, _vDrawPos.y);
    _VertexList[3].p = { test.x, test.y, 0.0f };
    _VertexList[3].t = { _rtUV.x1, _rtUV.y1 + _rtUV.h }; // uv반전 구현
    //_VertexList[3].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 + _rtUV.h };

    _pImmediateContext->UpdateSubresource(_pVertexBuffer, 0, NULL, &_VertexList.at(0), 0, 0);
}

void Object2D::SetMask(Texture* pMaskTex)
{
    _pMaskTex = pMaskTex;
}