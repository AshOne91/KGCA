#include "Interface.h"
#include "Input.h"

void Interface::Rotation()
{
    float fRadian = DegreeToRadian(_fAngleDegree);
    for (int iV = 0; iV < 4; iV++)
    {
        _InitVertexList[iV].p.x = _VertexList[iV].p.x * cos(fRadian) - _VertexList[iV].p.y * sin(fRadian);
        _InitVertexList[iV].p.y = _VertexList[iV].p.x * sin(fRadian) + _VertexList[iV].p.y * cos(fRadian);
    }
    _pImmediateContext->UpdateSubresource(
        _pVertexBuffer, NULL, NULL, &_InitVertexList.at(0), 0, 0);
}

bool Button::Init()
{
    return true;
}

bool Button::Frame()
{
    POINT ptMouse = I_Input._ptPos;
    if (Collision::RectToPoint(_rtCollision, ptMouse))
    {
        _currentState = UIState::UI_HOVER;
        _pCurrentTex = _pStateList[(int)UIState::UI_HOVER];
        if (I_Input.GetKey(VK_LBUTTON) == KEY_PUSH || I_Input.GetKey(VK_LBUTTON) == KEY_HOLD)
        {
            _currentState = UIState::UI_PUSH;
            _pCurrentTex = _pStateList[(int)UIState::UI_PUSH];
        }
        if (I_Input.GetKey(VK_LBUTTON) == KEY_UP)
        {
            _currentState = UIState::UI_SELECT;
        }
    }
    else
    {
        _pCurrentTex = _pStateList[(int)UIState::UI_NORMAL];
    }

    _VertexList[0].t = { 0.0f, 0.0f };
    _VertexList[1].t = { 1.0f, 0.0f };
    _VertexList[2].t = { 0.0f, 1.0f };
    _VertexList[3].t = { 1.0f, 1.0f };
    _pImmediateContext->UpdateSubresource(_pVertexBuffer, NULL, NULL, &_VertexList.at(0), 0, 0);
    return true;
}

bool Button::Render()
{
    BaseObject::PreRender();
    _pImmediateContext->PSSetShaderResources(0, 1, &_pCurrentTex->_pTextureSRV);
    BaseObject::PostRender();
    return true;
}

bool Button::Release()
{
    return true;
}

bool ListControl::Init()
{
    return true;
}

bool ListControl::Frame()
{
    for (auto data : _btnList)
    {
        data->Frame();
    }
    return true;
}

bool ListControl::Render()
{
    BaseObject::PreRender();
    _pImmediateContext->PSSetShaderResources(0, 1, &_pCurrentTex->_pTextureSRV);
    BaseObject::PostRender();

    for (auto data : _btnList)
    {
        data->Render();
    }
    return true;
}

bool ListControl::Release()
{
    return true;
}

void ListControl::UpdateVertexBuffer()
{
    _VertexList[0].p = { _vNDCPos.x, _vNDCPos.y, 0.0f };
    _VertexList[0].t = { _rtUV.x1, _rtUV.y1 };

    _VertexList[1].p = { _vNDCPos.x + _vDrawSize.x, _vNDCPos.y,  0.0f };
    _VertexList[1].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 };

    _VertexList[2].p = { _vNDCPos.x, _vNDCPos.y - _vDrawSize.y, 0.0f };
    _VertexList[2].t = { _rtUV.x1, _rtUV.y1 + _rtUV.h };

    _VertexList[3].p = { _vNDCPos.x + _vDrawSize.x, _vNDCPos.y - _vDrawSize.y, 0.0f };
    _VertexList[3].t = { _rtUV.x1 + _rtUV.w , _rtUV.y1 + _rtUV.h };

    _pImmediateContext->UpdateSubresource(
        _pVertexBuffer, NULL, NULL, &_VertexList.at(0), 0, 0);
}

void ListControl::SetRect(const Rect& rt)
{
    _rtInit = rt;
    _ptImageSize.x = _pTexture->_Desc.Width;
    _ptImageSize.y = _pTexture->_Desc.Height;
    float fPixelX = (1.0f / _pTexture->_Desc.Width) / 2.0f;
    float fPixelY = (1.0f / _pTexture->_Desc.Height) / 2.0f;
    // 90  -> 0 ~ 1
    _rtUV.x1 = 0.0f; // u
    // 1
    _rtUV.y1 = 0.0f; // v
    // 40
    _rtUV.w = 1.0f;
    // 60
    _rtUV.h = 1.0f;
}

void ListControl::ScreenToNDC()
{
    Vector2D	vDrawSize;
    vDrawSize.x = _rtInit.w / 2.0f;
    vDrawSize.y = _rtInit.h / 2.0f;
    _rtCollision.Set(
        _vPos.x - vDrawSize.x,
        _vPos.y - vDrawSize.y,
        _rtInit.w,
        _rtInit.h);

    // 0  ~ 800   -> 0~1 ->  -1 ~ +1
    _vNDCPos.x = (_rtCollision.x1 / g_rtClient.right) * 2.0f - 1.0f;
    _vNDCPos.y = -((_rtCollision.y1 / g_rtClient.bottom) * 2.0f - 1.0f);
    _vDrawSize.x = (_rtInit.w / (float)g_rtClient.right) * 2.0f;
    _vDrawSize.y = (_rtInit.h / (float)g_rtClient.bottom) * 2.0f;
}
