#include "Explosion.h"
#include "Spawner.h"
#include "GameWorld.h"
#include "ObjectManager.h"
#include "Circle.h"
#include "ObjectManager.h"
#include "SteeringBehaviors.h"
#include "SceneManager.h"
#include "DeadMonster.h"
#include "Utils.h"

bool Explosion::_bSoundInit = false;
std::vector<int> Explosion::_blankIndexList = std::vector<int>();
Sound* Explosion::pSound[2];
void Explosion::SetPosition(const Vector2D& vPos, const Vector2D& vCamera)
{
	Object2DComponent::SetPosition(vPos, vCamera);
	_transform.SetPostion(vPos);
	_vMovingPos = _vPos;
}

bool Explosion::Render()
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

void Explosion::UpdateVertexBuffer()
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

bool Explosion::Frame()
{
	_fMaxSpeed = 300.0f;
	_fSpeed = 200.0f;
	_vVelocity += _vDir * g_fSecondPerFrame * _fSpeed;
	_vVelocity.Truncate(_fMaxSpeed);
	_vMovingPos += _vVelocity * g_fSecondPerFrame;
	SetCameraSize(I_GameWorld.GetViewSize());
	SetCameraPos(I_GameWorld.GetCameraPos());
	SetPosition(_vMovingPos, _vCameraPos);
	EffectUpdate();
	Vector2D length = I_GameWorld.GetCameraPos() - _vMovingPos;
	if (length.Length() > 4344.5f * 0.5f)
	{
		DestroyObject(GetIndex());
	}
	return true;
}

bool Explosion::CInit()
{
	if (_bSoundInit == false)
	{
		for (int i = 0; i < 2; ++i)
		{
			pSound[i] = I_Sound.Load(L"../../resource/sfx/VS_ProjectileMagic_v04-03.ogg");
			_blankIndexList.push_back(i);
		}
		_bSoundInit = true;
	}
	Explosion::Init();
	_pSprite = I_Sprite.GetPtr(L"rtExplosion");
	Create(I_GameWorld.GetDevice(), I_GameWorld.GetDeviceImmediateContext(), L"../../data/shader/DefaultShapeMask.txt", L"../../data/bitmap1.bmp");
	Object2D::SetPosition(Vector2D(0.0f, 0.0f));
	CreateComponent<CircleComponent>();
	InitSprite();
	GetComponent<CircleComponent>()->fRadius = _tRect.w * 0.5f;
	_vDir = Vector2D(KSHCore::UTIL::RandomClamped(), KSHCore::UTIL::RandomClamped());
	_vDir.Normalize();
	if (_allockSoundIndex == -1)
	{
		if (_blankIndexList.size() > 0)
		{
			_allockSoundIndex = _blankIndexList.back();
			_blankIndexList.pop_back();
			pSound[_allockSoundIndex]->Stop();
			pSound[_allockSoundIndex]->PlayEffect();
		}
	}
	return true;
}

bool Explosion::CFrame()
{
	Explosion::Frame();
	return true;
}

bool Explosion::CRender()
{
	Explosion::Render();
	return true;
}

bool Explosion::CRelease()
{
	if (_allockSoundIndex != -1)
	{
		pSound[_allockSoundIndex]->Stop();
		_blankIndexList.push_back(_allockSoundIndex);
	}
	Explosion::Release();
	ComponentObject::CRelease();
	return true;
}

bool Explosion::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	if (eventType == EventType::CollisionIn)
	{
		ComponentObject* pComponent = static_cast<ComponentObject*>(msg->_pExtraInfo);
		Monster* pMonster = dynamic_cast<Monster*>(pComponent);
		if (pMonster != nullptr)
		{
			pMonster->Damanged(100.0f);
		}
	}
	return true;
}