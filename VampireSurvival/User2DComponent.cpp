#include "User2DComponent.h"
#include "Input.h"
#include "GameWorld.h"

void User2DComponent::UpdateVertexBuffer()
{
    _VertexList[0].p = { _vNDCPos.x, _vNDCPos.y, 0.0f };
    _VertexList[0].t = { _rtUV.x1, _rtUV.y1 };

    _VertexList[1].p = { _vNDCPos.x + _vDrawSize.x, _vNDCPos.y,  0.0f };
    _VertexList[1].t = { _rtUV.x1 + _rtUV.w, _rtUV.y1 };

    _VertexList[2].p = { _vNDCPos.x, _vNDCPos.y - _vDrawSize.y, 0.0f };
    _VertexList[2].t = { _rtUV.x1, _rtUV.y1 + _rtUV.h };

    _VertexList[3].p = { _vNDCPos.x + _vDrawSize.x, _vNDCPos.y - _vDrawSize.y, 0.0f };
    _VertexList[3].t = { _rtUV.x1 + _rtUV.w , _rtUV.y1 + _rtUV.h };

    Rotation();

    _pImmediateContext->UpdateSubresource(_pVertexBuffer, NULL, NULL, &_VertexList.at(0), 0, 0);
}

bool User2DComponent::Frame()
{
    Vector2D vPos = _vPos;
    _vDir = { 0,0 };
    if (I_Input.GetKey('W'))
    {
        _vDir.y = -1.0f;
        vPos.y += -1.0f * g_fSecondPerFrame * _fSpeed;
    }
    if (I_Input.GetKey('S'))
    {
        _vDir.y = 1.0f;
        vPos.y += 1.0f * g_fSecondPerFrame * _fSpeed;
    }
    if (I_Input.GetKey('A'))
    {
        _vDir.x = -1.0f;
        vPos.x += -1.0f * g_fSecondPerFrame * _fSpeed;
    }
    if (I_Input.GetKey('D'))
    {
        _vDir.x = 1.0f;
        vPos.x += 1.0f * g_fSecondPerFrame * _fSpeed;
    }
    _vPos = vPos;
    return true;
}

bool User2DComponent::Render()
{
    this->PreRender();
    _pImmediateContext->PSSetShaderResources(1, 1,
        &(this->_pMaskTex->_pTextureSRV));
    this->PostRender();
    return true;
}

bool User2DComponent::CInit()
{
    User2DComponent::Init();
    Texture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");
    this->Create(I_GameWorld.GetDevice(), I_GameWorld.GetDeviceImmediateContext(),
    L"../../data/shader/DefaultShapeMask.txt",
    L"../../data/bitmap1.bmp");
    this->SetMask(pMaskTex);
    this->_fSpeed = 300.0f;
    this->SetRect({ 90, 2, 40, 60 });
    this->SetPosition({ 0.0f,0.0f });
    return true;
}

bool User2DComponent::CFrame()
{
    User2DComponent::Frame();
    I_GameWorld.SetCameraPos(_vPos);
    this->SetCameraSize(I_GameWorld.GetViewSize());
    this->SetCameraPos(I_GameWorld.GetCameraPos());
    this->SetPosition(this->_vPos, I_GameWorld.GetCameraPos());
    return true;
}

bool User2DComponent::CRender()
{
    User2DComponent::Render();
    return true;
}

bool User2DComponent::CRelease()
{
    User2DComponent::Release();
    return true;
}

bool User2DComponent::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
    return true;
}
