#include "User2DComponent.h"
#include "Input.h"
#include "GameWorld.h"
#include "Circle.h"
#include "ObjectManager.h"
#include "Monster.h"
#include "Skill.h"
#include "Explosion.h"
#include "Utils.h"
#include "EventManager.h"

int g_iMaxHP = 100;
int g_iCurrentHP = 100;
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
    if (_explosionCounter.IsFinished())
    {
        _explosionCounter.Start(5000);
        auto pExplosion = CreateObject<Explosion>();
        pExplosion->SetPosition(_vMovingPos, I_GameWorld.GetCameraPos());
    }
    _vVelocity = { 0,0 };
    _bAnimation = false;
    if (I_Input.GetKey('W'))
    {
        _bAnimation = true;
        _vVelocity.y = -1.0f;
    }
    if (I_Input.GetKey('S'))
    {
        _bAnimation = true;
        _vVelocity.y = 1.0f;
    }
    if (I_Input.GetKey('A'))
    {
        _bAnimation = true;
        _bFlip = true;
        _vVelocity.x = -1.0f;
    }
    if (I_Input.GetKey('D'))
    {
        _bAnimation = true;
        _bFlip = false;
        _vVelocity.x = 1.0f;
    }
    _fSpeed = 100.0f;
    _vVelocity *= _fSpeed;
    _vMovingPos += _vVelocity * g_fSecondPerFrame;
    if (_vVelocity.LengthSq() > Epsilon)
    {
        _vHeading = _vVelocity.Identity();
        _vSide = _vHeading.Perp();
    }

    I_GameWorld.SetCameraPos(_vMovingPos);
    SetCameraSize(I_GameWorld.GetViewSize());
    SetCameraPos(I_GameWorld.GetCameraPos());
    SetPosition(_vMovingPos, I_GameWorld.GetCameraPos());
    EffectUpdate();
    return true;
}

void User2DComponent::SetPosition(const Vector2D& vPos, const Vector2D& vCamera)
{
    Object2DComponent::SetPosition(vPos, vCamera);
    _transform.SetPostion(_vPos);
    _vMovingPos = _vPos;
}

bool User2DComponent::Render()
{
    _pSprite->SetCameraSize(I_GameWorld.GetViewSize());
    _pSprite->SetCameraPos(I_GameWorld.GetCameraPos());
    _pSprite->SetRect(_tRect);
    _pSprite->SetPosition(_vMovingPos, _vCameraPos);
    if (_bFlip == true)
    {
        _pSprite->UpdateVertexBufferFlip();
    }
    _pSprite->Render();
    return true;
}

bool User2DComponent::CInit()
{
    g_iMaxHP = 100;
    g_iCurrentHP = 100;
    User2DComponent::Init();
    _pSprite = I_Sprite.GetPtr(L"rtUser");
    Create(I_GameWorld.GetDevice(), I_GameWorld.GetDeviceImmediateContext(), L"../../data/shader/DefaultShapeMask.txt", L"../../data/bitmap1.bmp");
    Object2D::SetPosition(Vector2D(0.0f, 0.0f));
    CreateComponent<CircleComponent>();
    GetComponent<CircleComponent>()->fRadius = 5.0f;
    CreateObject<Skill>();
    InitSprite();
    _fSpeed = 300.0f;
    _explosionCounter.Start(5000);
    return true;
}

bool User2DComponent::CFrame()
{
    User2DComponent::Frame();
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
    ComponentObject::CRelease();
    return true;
}

bool User2DComponent::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
    if (eventType == EventType::CollisionIn)
    {
        ComponentObject* pComponent = static_cast<ComponentObject*>(msg->_pExtraInfo);
        Monster* pMonster = dynamic_cast<Monster*>(pComponent);
        if (pMonster != nullptr)
        {
            g_iCurrentHP -= 1;
            g_iCurrentHP = KSHCore::UTIL::Maximum(0, g_iCurrentHP);
            I_EventManager.PostNotifycation(EventType::HpChange, NotifyType::BroadCast, this, nullptr);
        }
    }
    return true;
}
