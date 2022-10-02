#include "User2D.h"
#include "Input.h"
#include "GameWorld.h"
#include "Circle.h"
#include "ObjectManager.h"
#include "Monster.h"

void User2D::UpdateVertexBuffer()
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

bool User2D::Frame()
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
    I_GameWorld.SetCameraPos(_vPos);
    SetCameraSize(I_GameWorld.GetViewSize());
    SetCameraPos(I_GameWorld.GetCameraPos());
    SetPosition(this->_vPos, I_GameWorld.GetCameraPos());
    return true;
}

void User2D::SetPosition(const Vector2D& vPos, const Vector2D& vCamera)
{
    Object2D::SetPosition(vPos, vCamera);
    _transform.SetPostion(_vPos);
}

bool User2D::Render()
{
    this->PreRender();
    _pImmediateContext->PSSetShaderResources(1, 1,
        &(this->_pMaskTex->_pTextureSRV));
    this->PostRender();
    return true;
}

bool User2D::CInit()
{
    User2D::Init();
    Texture* pMaskTex = I_Tex.Load(L"../../data/bitmap2.bmp");
    this->Create(I_GameWorld.GetDevice(), I_GameWorld.GetDeviceImmediateContext(),
    L"../../data/shader/DefaultShapeMask.txt",
    L"../../data/bitmap1.bmp");
    SetMask(pMaskTex);
    _fSpeed = 300.0f;
    SetRect({ 90, 2, 40, 60 });
    Object2D::SetPosition(Vector2D( 0.0f,0.0f ));
    CreateComponent<CircleComponent>();
    GetComponent<CircleComponent>()->fRadius = 5.0f;
    return true;
}

bool User2D::CFrame()
{
    User2D::Frame();
    return true;
}

bool User2D::CRender()
{
    User2D::Render();
    return true;
}

bool User2D::CRelease()
{
    User2D::Release();
    ComponentObject::CRelease();
    return true;
}

bool User2D::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
    if (eventType == EventType::CollisionIn)
    {
        ComponentObject* pComponent = static_cast<ComponentObject*>(msg->_pExtraInfo);
        Monster* pMonster = dynamic_cast<Monster*>(pComponent);
        if (pMonster != nullptr)
        {
            I_ObjectManager.DestroyObject(pMonster->GetIndex());
        }
    }

    if (eventType == EventType::CollisionOut)
    {
        int j = 0;
    }
    return true;
}
