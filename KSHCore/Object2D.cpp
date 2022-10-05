#include "Object2D.h"

/*Vector2D Func(float radian, Vector2D test, float posX, float posY)
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
}*/

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
    //_vNDCPos.x = (_vPos.x / g_rtClient.right) * 2.0f - 1.0f;
    //_vNDCPos.y = -((_vPos.y / g_rtClient.bottom) * 2.0f - 1.0f);
    //_vDrawSize.x = (_rtInit.w / g_rtClient.right) * 2.0f;
    //_vDrawSize.y = (_rtInit.h / g_rtClient.bottom) * 2.0f;

    Vector2D vDrawSize;
    vDrawSize.x = _rtInit.w / 2.0f;
    vDrawSize.y = _rtInit.h / 2.0f;
    _rtCollision.Set(
        _vPos.x - vDrawSize.x,
        _vPos.y - vDrawSize.y,
        _rtInit.w,
        _rtInit.h);
    //// 0  ~ 800   -> 0~1 ->  -1 ~ +1
    _vNDCPos.x = (_rtCollision.x1 / g_rtClient.right) * 2.0f - 1.0f;
    _vNDCPos.y = -((_rtCollision.y1 / g_rtClient.bottom) * 2.0f - 1.0f);
    _vDrawSize.x = (_rtInit.w / (float)g_rtClient.right) * 2.0f;
    _vDrawSize.y = (_rtInit.h / (float)g_rtClient.bottom) * 2.0f;
}

// 월드좌표 -> 뷰 좌표 -> NDC 좌표
void Object2D::ScreenToCamera(const Vector2D& vCameraPos, const Vector2D& vViewPort)
{
    //// 0  ~ 800   -> 0~1 ->  -1 ~ +1
    Vector2D vPos = _vPos;
    Vector2D vDrawSize;
    vDrawSize.x = _rtInit.w / 2.0f;
    vDrawSize.y = _rtInit.h / 2.0f;
    _rtCollision.Set(
        _vPos.x - vDrawSize.x,
        _vPos.y - vDrawSize.y,
        _rtInit.w,
        _rtInit.h);

    vPos.x = _rtCollision.x1 - vCameraPos.x;
    vPos.y = _rtCollision.y1 - vCameraPos.y;
    //// 0  ~ 800   -> 0~1 ->  -1 ~ +1
    _vNDCPos.x = vPos.x * (2.0f / vViewPort.x);
    _vNDCPos.y = vPos.y * (2.0f / vViewPort.y) * -1.0f;
    _vDrawSize.x = (_rtInit.w / vViewPort.x) * 2.0f;
    _vDrawSize.y = (_rtInit.h / vViewPort.y) * 2.0f;
}

void Object2D::SetPosition(const Vector2D& vPos, const Vector2D& vCamera)
{
    _vBeforePos = _vPos;
    _vPos = vPos;
    ScreenToCamera(vCamera, _vViewSize);
    UpdateVertexBuffer();
    _vOffsetPos = _vPos - _vBeforePos;
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

    /*//전체 텍스쳐 크기에서 0~1사이의 값 셋팅(얻어올 텍스쳐 스프라이트의 좌표)
    // 90 -> 0 ~ 1
    float fPixelX = (1.0f / _pTexture->_Desc.Width) / 2.0f;
    float fPixelY = (1.0f / _pTexture->_Desc.Height) / 2.0f;
    // 90  -> 0 ~ 1
    _rtUV.x1 = rt.x1 / _ptImageSize.x + fPixelX; // u
    // 1
    _rtUV.y1 = rt.y1 / _ptImageSize.y + fPixelY; // v
    // 40
    _rtUV.w = rt.w / _ptImageSize.x;
    // 60
    _rtUV.h = rt.h / _ptImageSize.y;*/
    /*_rtUV.x1 = rt.x1 / _ptImageSize.x;
// 1
    _rtUV.y1 = rt.y1 / _ptImageSize.y;
    // 40
    _rtUV.w = rt.w / _ptImageSize.x;
    // 60
    _rtUV.h = rt.h / _ptImageSize.y;*/
    float fPixelX = (1.0f / _pTexture->_Desc.Width) / 2.0f;
    float fPixelY = (1.0f / _pTexture->_Desc.Height) / 2.0f;
    _rtUV.x1 = rt.x1 / _ptImageSize.x + fPixelX;
    _rtUV.y1 = rt.y1 / _ptImageSize.y + fPixelY;
    _rtUV.w = rt.w / _ptImageSize.x;
    _rtUV.h = rt.h / _ptImageSize.y;
}

// 화면 좌표 -> NDC(Noramlize Device Coordinate)이며, 이 공간은 투영(Projection) 행렬에 정의
void Object2D::SetPosition(const Vector2D& vPos)
{
    _vBeforePos = _vPos;
    _vPos = vPos;
    ScreenToNDC();
    UpdateVertexBuffer();
    _vOffsetPos = _vPos - _vBeforePos;
}

void Object2D::SetDirection(const Vector2D& vDir)
{
    _vDir = vDir;
}

void Object2D::UpdateVertexBuffer()
{
   //// Vector2D Center;
   // //Center.x = _vNDCPos.x + _vDrawSize.x;
   // //Center.y = _vNDCPos.y - _vDrawSize.y;
   // //Center *= 0.5f;
   // //float radian = g_fGameTimer * 0.1f;
   // //Vector2D test = Func(radian, Vector2D(_vNDCPos.x, _vNDCPos.y), Center.x, Center.y);
   // _VertexList[0].p = { test.x, test.y, 0.0f };
   // _VertexList[0].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 }; // uv반전 구현
   // //_VertexList[0].t = { _rtUV.x1, _rtUV.y1 }; 

   // //test = Func(radian, Vector2D(_vNDCPos.x + _vDrawSize.x, _vNDCPos.y), Center.x, Center.y);
   // _VertexList[1].p = { test.x, test.y,  0.0f };
   // _VertexList[1].t = { _rtUV.x1, _rtUV.y1 }; // uv반전 구현
   // //_VertexList[1].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 };


   // //test = Func(radian, Vector2D(_vNDCPos.x, _vNDCPos.y - _vDrawSize.y), Center.x, Center.y);
   // _VertexList[2].p = { test.x, test.y, 0.0f };
   // _VertexList[2].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 + _rtUV.h }; // uv반전 구현
   // //_VertexList[2].t = { _rtUV.x1, _rtUV.y1 + _rtUV.h };

   // /*_VertexList[3].p = _VertexList[2].p;
   // _VertexList[3].t = _VertexList[2].t;

   // _VertexList[4].p = _VertexList[1].p;
   // _VertexList[4].t = _VertexList[1].t;

   // _VertexList[5].p = { _vNDCPos.x + _vDrawSize.x, _vNDCPos.y - _vDrawSize.y, 0.0f };
   // _VertexList[5].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 + _rtUV.h };*/ //인덱스 버퍼 사용으로 주석처리

   // //test = Func(radian, Vector2D(_vNDCPos.x + _vDrawSize.x, _vNDCPos.y - _vDrawSize.y), Center.x, Center.y);
   // _VertexList[3].p = { test.x, test.y, 0.0f };
   // _VertexList[3].t = { _rtUV.x1, _rtUV.y1 + _rtUV.h }; // uv반전 구현
   // //_VertexList[3].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 + _rtUV.h };

    /*Vector2D Center;
    Center.x = _vNDCPos.x + _vDrawSize.x;
    Center.y = _vNDCPos.y + _vDrawSize.y;
    Center *= 0.5f;
    float radian = g_fGameTimer * 0.1f;
    Vector2D test = Func(radian, Vector2D(_vNDCPos.x, _vNDCPos.y), Center.x, Center.y);*/

    _VertexList[0].p = { _vNDCPos.x, _vNDCPos.y, 0.0f };
    _VertexList[0].t = { _rtUV.x1, _rtUV.y1 };
    //_VertexList[0].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 };


    //test = Func(radian, Vector2D(_vNDCPos.x + _vDrawSize.x, _vNDCPos.y), Center.x, Center.y);
    _VertexList[1].p = { _vNDCPos.x + _vDrawSize.x, _vNDCPos.y,  0.0f };
    _VertexList[1].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 };
    //_VertexList[1].t = { _rtUV.x1, _rtUV.y1 };

    //test = Func(radian, Vector2D(_vNDCPos.x, _vNDCPos.y - _vDrawSize.y), Center.x, Center.y);
    _VertexList[2].p = { _vNDCPos.x, _vNDCPos.y - _vDrawSize.y, 0.0f };
    _VertexList[2].t = { _rtUV.x1, _rtUV.y1 + _rtUV.h };
    //_VertexList[2].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 + _rtUV.h };

    /*   m_VertexList[3].p = m_VertexList[2].p;
       m_VertexList[3].t = m_VertexList[2].t;

       m_VertexList[4].p = m_VertexList[1].p;
       m_VertexList[4].t = m_VertexList[1].t;*/

    //test = Func(radian, Vector2D(_vNDCPos.x + _vDrawSize.x, _vNDCPos.y - _vDrawSize.y), Center.x, Center.y);
    _VertexList[3].p = { _vNDCPos.x + _vDrawSize.x, _vNDCPos.y - _vDrawSize.y, 0.0f };
    _VertexList[3].t = { _rtUV.x1 + _rtUV.w , _rtUV.y1 + _rtUV.h };
    //_VertexList[3].t = { _rtUV.x1 , _rtUV.y1 + _rtUV.h };

    Rotation();

    _pImmediateContext->UpdateSubresource(
        _pVertexBuffer, NULL, NULL, &_VertexList.at(0), 0, 0);
}

void Object2D::UpdateVertexBufferFlip()
{
    _VertexList[0].p = { _vNDCPos.x, _vNDCPos.y, 0.0f };
    _VertexList[0].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 };

    _VertexList[1].p = { _vNDCPos.x + _vDrawSize.x, _vNDCPos.y,  0.0f };
    _VertexList[1].t = { _rtUV.x1, _rtUV.y1 };

    _VertexList[2].p = { _vNDCPos.x, _vNDCPos.y - _vDrawSize.y, 0.0f };
    _VertexList[2].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 + _rtUV.h };

    _VertexList[3].p = { _vNDCPos.x + _vDrawSize.x, _vNDCPos.y - _vDrawSize.y, 0.0f };
    _VertexList[3].t = { _rtUV.x1 , _rtUV.y1 + _rtUV.h };

    Rotation();

    _pImmediateContext->UpdateSubresource(
        _pVertexBuffer, NULL, NULL, &_VertexList.at(0), 0, 0);
}

void Object2D::SetMask(Texture* pMaskTex)
{
    _pMaskTex = pMaskTex;
}
