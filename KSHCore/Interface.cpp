#include "Interface.h"
#include "Input.h"

/*void Interface::Rotation()
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
}*/

bool Interface::Frame()
{
    POINT ptMouse = I_Input._ptPos;
    if (Collision::RectToPoint(_rtCollision, ptMouse))
    {
        _currentState = UIState::UI_HOVER;
        _pCurrentTex = _eventState._pStateList[(int)UIState::UI_HOVER];
        if (I_Input.GetKey(VK_LBUTTON) == KEY_PUSH || I_Input.GetKey(VK_LBUTTON) == KEY_HOLD)
        {
            _currentState = UIState::UI_PUSH;
            _pCurrentTex = _eventState._pStateList[(int)UIState::UI_PUSH];
        }
        if (I_Input.GetKey(VK_LBUTTON) == KEY_UP)
        {
            _currentState = UIState::UI_SELECT;
        }
    }
    else
    {
        _pCurrentTex = _eventState._pStateList[(int)UIState::UI_NORMAL];
    }
    return true;
}

void Interface::FadeInOut(float fAlpha)
{
    _VertexList[0].c = { 1.0f, 1.0f, 1.0f, fAlpha };
    _VertexList[1].c = { 1.0f, 1.0f, 1.0f, fAlpha };
    _VertexList[2].c = { 1.0f, 1.0f, 1.0f, fAlpha };
    _VertexList[3].c = { 1.0f, 1.0f, 1.0f, fAlpha };
    _pImmediateContext->UpdateSubresource(_pVertexBuffer, NULL, NULL, &_VertexList.at(0), 0, 0);
}

void Interface::AddChild(Interface* pUI)
{
    _pChildList.push_back(pUI);
}

bool Interface::SetTextureState(const std::vector<W_STR>& texStateList)
{
    if (texStateList.size() <= 0)
    {
        _pCurrentTex = _pTexture;
        _eventState._pStateList.push_back(_pTexture);
        _eventState._pStateList.push_back(_pTexture);
        _eventState._pStateList.push_back(_pTexture);
        _eventState._pStateList.push_back(_pTexture);
        return true;
    }

    Texture* pTexture = nullptr;
    if (!texStateList[0].empty())
    {
        pTexture = I_Tex.Load(texStateList[0]);
        _pCurrentTex = pTexture;
        _eventState._pStateList[(int)UIState::UI_NORMAL] = pTexture;
    }

    if (!texStateList[1].empty())
    {
        pTexture = I_Tex.Load(texStateList[1]);
        _eventState._pStateList[(int)UIState::UI_HOVER] = pTexture;
    }

    if (!texStateList[2].empty())
    {
        pTexture = I_Tex.Load(texStateList[2]);
        _eventState._pStateList[(int)UIState::UI_PUSH] = pTexture;
    }

    if (!texStateList[3].empty())
    {
        pTexture = I_Tex.Load(texStateList[3]);
        _eventState._pStateList[(int)UIState::UI_DIS] = pTexture;
    }

    return true;
}

bool Interface::SetAttribute(const Vector2D& vPos, const Rect& rt, Sprite* pSprite)
{
    Init();
    SetRect(rt);
    SetPosition(vPos);
    _pSprite = pSprite;
    if (pSprite->_texArray.size() > 0)
    {
        _pCurrentTex = _pTexture;
        _eventState._pStateList = pSprite->_pTexArray;
    }
    return true;
}

bool Interface::SetAttribute(const Vector2D& vPos, const Rect& rt, const std::vector<W_STR>& texStateList)
{
    Init();
    SetRect(rt);
    SetPosition(vPos);
    SetTextureState(texStateList);
    return true;
}

bool Interface::SetAttribute(const Vector2D& vPos, const std::vector<W_STR>& texStateList)
{
    Init();
    _ptImageSize.x = _pTexture->_Desc.Width;
    _ptImageSize.y = _pTexture->_Desc.Height;
    Rect rt = { 0, 0, (float)_ptImageSize.x, (float)_ptImageSize.y };
    SetRect(rt);
    SetPosition(vPos);
    SetTextureState(texStateList);
    return true;
}

bool Interface::SetDrawList(float fScaleX0, float fScaleX1, float fScaleY0, float fScaleY1, float fScaleU0, float fScaleU1, float fScaleV0, float fScaleV1)
{
    _rtDrawList.resize(9);
    for (int iSub = 0; iSub < _rtDrawList.size(); iSub++)
    {
        _rtDrawList[iSub] = new Interface;
        _rtDrawList[iSub]->Create(_pd3dDevice, _pImmediateContext,
            _szShaderName,
            _szTextureName);
    }

    Rect rt = _rtCollision;
    Vector2D  vCenter = _vPos;
    float fX[4];
    fX[0] = _rtCollision.x1;
    fX[1] = fX[0] + _rtCollision.w * fScaleX0;
    fX[2] = _rtCollision.x2 - (_rtCollision.w * fScaleX1);
    fX[3] = _rtCollision.x2;
    float fY[4];
    fY[0] = _rtCollision.y1;
    fY[1] = fY[0] + _rtCollision.h * fScaleY0;
    fY[2] = _rtCollision.y2 - (_rtCollision.h * fScaleY1);
    fY[3] = _rtCollision.y2;
    float fU[4];
    fU[0] = 0.0f;
    fU[1] = fU[0] + fScaleU0;
    fU[2] = 1.0f - fU[1];
    fU[3] = 1.0f;
    float fV[4];
    fV[0] = 0.0f;
    fV[1] = fV[0] + fScaleV0;
    fV[2] = 1.0f - fV[1];
    fV[3] = 1.0f;

    vCenter.x = (fX[0] + fX[1]) * 0.5f;
    vCenter.y = (fY[0] + fY[1]) * 0.5f;
    _rtDrawList[0]->_rtInit.Set(0, 0, fX[1] - fX[0], fY[1] - fY[0]);
    _rtDrawList[0]->_rtUV.x1 = fU[0];
    _rtDrawList[0]->_rtUV.y1 = fV[0];
    _rtDrawList[0]->_rtUV.w = fU[1] - fU[0];
    _rtDrawList[0]->_rtUV.h = fV[1] - fV[0];
    _rtDrawList[0]->SetPosition(vCenter);

    vCenter.x = (fX[2] + fX[1]) * 0.5f;
    _rtDrawList[1]->_rtInit.Set(fX[1], fY[0], fX[2] - fX[1], fY[1] - fY[0]);
    _rtDrawList[1]->_rtUV.x1 = fU[1];
    _rtDrawList[1]->_rtUV.y1 = fV[0];
    _rtDrawList[1]->_rtUV.w = fU[2] - fU[1];
    _rtDrawList[1]->_rtUV.h = fV[1] - fV[0];
    _rtDrawList[1]->SetPosition(vCenter);

    vCenter.x = (fX[3] + fX[2]) * 0.5f;
    _rtDrawList[2]->_rtInit.Set(fX[2], fY[0], fX[3] - fX[2], fY[1] - fY[0]);
    _rtDrawList[2]->_rtUV.x1 = fU[2];
    _rtDrawList[2]->_rtUV.y1 = fV[0];
    _rtDrawList[2]->_rtUV.w = fU[3] - fU[2];
    _rtDrawList[2]->_rtUV.h = fV[1] - fV[0];
    _rtDrawList[2]->SetPosition(vCenter);

    // 2
    vCenter.x = (fX[0] + fX[1]) * 0.5f;
    vCenter.y = (fY[2] + fY[1]) * 0.5f;
    _rtDrawList[3]->_rtInit.Set(0, 0, fX[1] - fX[0], fY[2] - fY[1]);
    _rtDrawList[3]->_rtUV.x1 = fU[0];
    _rtDrawList[3]->_rtUV.y1 = fV[1];
    _rtDrawList[3]->_rtUV.w = fU[1] - fU[0];
    _rtDrawList[3]->_rtUV.h = fV[2] - fV[1];
    _rtDrawList[3]->SetPosition(vCenter);

    vCenter.x = (fX[2] + fX[1]) * 0.5f;
    _rtDrawList[4]->_rtInit.Set(fX[1], fY[1], fX[2] - fX[1], fY[2] - fY[1]);
    _rtDrawList[4]->_rtUV.x1 = fU[1];
    _rtDrawList[4]->_rtUV.y1 = fV[1];
    _rtDrawList[4]->_rtUV.w = fU[2] - fU[1];
    _rtDrawList[4]->_rtUV.h = fV[2] - fV[1];
    _rtDrawList[4]->SetPosition(vCenter);

    vCenter.x = (fX[3] + fX[2]) * 0.5f;
    _rtDrawList[5]->_rtInit.Set(fX[2], fY[1], fX[3] - fX[2], fY[2] - fY[1]);
    _rtDrawList[5]->_rtUV.x1 = fU[2];
    _rtDrawList[5]->_rtUV.y1 = fV[1];
    _rtDrawList[5]->_rtUV.w = fU[3] - fU[2];
    _rtDrawList[5]->_rtUV.h = fV[2] - fV[1];
    _rtDrawList[5]->SetPosition(vCenter);

    // 3
    vCenter.x = (fX[0] + fX[1]) * 0.5f;
    vCenter.y = (fY[3] + fY[2]) * 0.5f;
    _rtDrawList[6]->_rtInit.Set(0, 0, fX[1] - fX[0], fY[3] - fY[2]);
    _rtDrawList[6]->_rtUV.x1 = fU[0];
    _rtDrawList[6]->_rtUV.y1 = fV[2];
    _rtDrawList[6]->_rtUV.w = fU[1] - fU[0];
    _rtDrawList[6]->_rtUV.h = fV[3] - fV[2];
    _rtDrawList[6]->SetPosition(vCenter);

    vCenter.x = (fX[2] + fX[1]) * 0.5f;
    _rtDrawList[7]->_rtInit.Set(fX[1], fY[2], fX[2] - fX[1], fY[3] - fY[2]);
    _rtDrawList[7]->_rtUV.x1 = fU[1];
    _rtDrawList[7]->_rtUV.y1 = fV[2];
    _rtDrawList[7]->_rtUV.w = fU[2] - fU[1];
    _rtDrawList[7]->_rtUV.h = fV[3] - fV[2];
    _rtDrawList[7]->SetPosition(vCenter);

    vCenter.x = (fX[3] + fX[2]) * 0.5f;
    _rtDrawList[8]->_rtInit.Set(fX[2], fY[2], fX[3] - fX[2], fY[3] - fY[2]);
    _rtDrawList[8]->_rtUV.x1 = fU[2];
    _rtDrawList[8]->_rtUV.y1 = fV[2];
    _rtDrawList[8]->_rtUV.w = fU[3] - fU[2];
    _rtDrawList[8]->_rtUV.h = fV[3] - fV[2];
    _rtDrawList[8]->SetPosition(vCenter);
    return true;
}

bool Button::Init()
{
    return true;
}

bool Button::Frame()
{
    Interface::Frame();
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

void Button::SetRect(const Rect& rt)
{
    _rtInit = rt;
    _ptImageSize.x = _pTexture->_Desc.Width;
    _ptImageSize.y = _pTexture->_Desc.Height;
    // 90  -> 0 ~ 1
    _rtUV.x1 = 0.0f; // u
    // 1
    _rtUV.y1 = 0.0f; // v
    // 40
    _rtUV.w = 1.0f;
    // 60
    _rtUV.h = 1.0f;
}

bool ListControl::Init()
{
    return true;
}

bool ListControl::Frame()
{
    for (auto data : _pChildList)
    {
        Vector2D pos = data->_vPos + _vOffsetPos;
        data->SetPosition(pos);
        data->Frame();
    }
    return true;
}

bool ListControl::Render()
{
    BaseObject::PreRender();
    _pImmediateContext->PSSetShaderResources(0, 1, &_pCurrentTex->_pTextureSRV);
    BaseObject::PostRender();

    for (auto data : _pChildList)
    {
        data->Render();
    }
    return true;
}

bool ListControl::Release()
{
    for (auto data : _pChildList)
    {
        data->Release();
        delete data;
    }
    Interface::Release();
    return true;
}

void ListControl::SetRect(const Rect& rt)
{
    _rtInit = rt;
    _ptImageSize.x = _pTexture->_Desc.Width;
    _ptImageSize.y = _pTexture->_Desc.Height;
    // 90  -> 0 ~ 1
    _rtUV.x1 = 0.0f; // u
    // 1
    _rtUV.y1 = 0.0f; // v
    // 40
    _rtUV.w = 1.0f;
    // 60
    _rtUV.h = 1.0f;
}

bool Dialog::Init()
{
    return true;
}

bool Dialog::Frame()
{
    Interface::Frame();

    for (int iSub = 0; iSub < _rtDrawList.size(); iSub++)
    {
        Vector2D pos = _rtDrawList[iSub]->_vPos + _vOffsetPos;
        _rtDrawList[iSub]->SetPosition(pos);
    }
    for (int iChild = 0; iChild < _pChildList.size(); iChild++)
    {
        Vector2D pos = _pChildList[iChild]->_vPos + _vOffsetPos;
        _pChildList[iChild]->SetPosition(pos);
        _pChildList[iChild]->Frame();
    }
    return true;
}

bool Dialog::Render()
{
    for (int iSub = 0; iSub < _rtDrawList.size(); ++iSub)
    {
        _rtDrawList[iSub]->Render();
    }

    for (int iChild = 0; iChild < _pChildList.size(); ++iChild)
    {
        _pChildList[iChild]->Render();
    }
    return false;
}

bool Dialog::Release()
{
    for (auto data : _rtDrawList)
    {
        data->Release();
        delete data;
    }

    for (auto data : _pChildList)
    {
        data->Release();
        delete data;
    }
    Interface::Release();
    return true;
}
