#include "Skill.h"
#include "SpriteManager.h"
#include "Circle.h"
#include "GameWorld.h"
#include "Message.h"
#include "Monster.h"
#include "Hit.h"

void Skill::UpdateVertexBuffer()
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

bool Skill::Frame()
{
	_vMovingPos = I_GameWorld.GetCameraPos();
	SetCameraSize(I_GameWorld.GetViewSize());
	SetCameraPos(I_GameWorld.GetCameraPos());
	SetPosition(_vMovingPos, I_GameWorld.GetCameraPos());
	EffectUpdate();
	return true;
}

void Skill::SetPosition(const Vector2D& vPos, const Vector2D& vCamera)
{
	Object2DComponent::SetPosition(vPos, vCamera);
	_transform.SetPostion(vPos);
	_vMovingPos = _vPos;
}

bool Skill::Render()
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

bool Skill::CInit()
{
	Object2DComponent::Init();
	_pSprite = I_Sprite.GetPtr(L"rtAurora");
	Create(I_GameWorld.GetDevice(), I_GameWorld.GetDeviceImmediateContext(), L"../../data/shader/DefaultShapeMask.txt", L"../../data/bitmap1.bmp");
	Object2D::SetPosition(Vector2D(0.0f, 0.0f));
	CreateComponent<CircleComponent>();
	InitSprite();
	GetComponent<CircleComponent>()->fRadius = _tRect.w * 0.5f;
	return true;
}

bool Skill::CFrame()
{
	Skill::Frame();
	return true;
}

bool Skill::CRender()
{
	Skill::Render();
	return true;
}

bool Skill::CRelease()
{
	Skill::Release();
	ComponentObject::CRelease();
	return true;
}

bool Skill::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	if (eventType == EventType::CollisionIn)
	{
		ComponentObject* pComponent = static_cast<ComponentObject*>(msg->_pExtraInfo);
		Monster* pMonster = dynamic_cast<Monster*>(pComponent);
		if (pMonster != nullptr)
		{
			if (pMonster->IsImmune())
			{
				return true;
			}
			auto pHit = CreateObject<Hit>();
			pHit->SetPosition(pMonster->_vMovingPos, I_GameWorld.GetCameraPos());
			Vector2D ToMonster = pMonster->_vMovingPos - _vMovingPos;
			float DistFrom = ToMonster.Length() ;
			pMonster->SetPosition(pMonster->_vMovingPos + (ToMonster / DistFrom) * 10.0f, I_GameWorld.GetCameraPos());
			pMonster->Damanged(7.0f);
		}
	}
	if (eventType == EventType::CollisionOut)
	{
		ComponentObject* pComponent = static_cast<ComponentObject*>(msg->_pExtraInfo);
		Monster* pMonster = dynamic_cast<Monster*>(pComponent);
		if (pMonster != nullptr)
		{
			pMonster->_forceList.clear();
			return true;
		}
	}
	return true;
}
