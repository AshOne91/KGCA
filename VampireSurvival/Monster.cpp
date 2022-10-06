#include "Monster.h"
#include "Spawner.h"
#include "GameWorld.h"
#include "ObjectManager.h"
#include "Circle.h"
#include "ObjectManager.h"
#include "SteeringBehaviors.h"
#include "SceneManager.h"
#include "DeadMonster.h"
#include "SoundManager.h"


extern unsigned __int64 g_CreateMonster;
extern unsigned __int64 g_currentMonster;
extern unsigned __int64 g_DeadMonster;

bool Monster::_bSoundInit = false;
std::vector<int> Monster::_blankIndexList = std::vector<int>();
Sound* Monster::pSound[5];
void Monster::SetPosition(const Vector2D& vPos, const Vector2D& vCamera)
{
	Object2DComponent::SetPosition(vPos, vCamera);
	_transform.SetPostion(vPos);
	_vMovingPos = _vPos;
}

bool Monster::Render()
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

void Monster::UpdateVertexBuffer()
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

bool Monster::Frame()
{
	_fSpeed = 100.0f;
	_fMaxSpeed = 100.0f;
	Vector2D force = GetSteeringBehaviours()->Seek(I_GameWorld.GetCameraPos());

	for(auto& data : _forceList)
	{
		force += data;
	}
	Vector2D acceleration = force / 1.0f;
	_vVelocity += acceleration * g_fSecondPerFrame;// *_fSpeed;
	_vVelocity.Truncate(_fMaxSpeed);
	if (_immuneCounter.IsFinished())
	{
		_bImmue = false;
	}
	if (_bImmue == true)
	{
		_vVelocity *= 0.98f;
	}

	_vMovingPos += _vVelocity * g_fSecondPerFrame;
	if (_vVelocity.LengthSq() > 0.00000001)
	{
		_vHeading = _vVelocity.Identity();
		_vSide = _vHeading.Perp();
	}
	if (I_GameWorld.GetCameraPos().x - _vMovingPos.x > 0.0f)
	{
		_bFlip = true;
	}
	else
	{
		_bFlip = false;
	}
	SetCameraSize(I_GameWorld.GetViewSize());
	SetCameraPos(I_GameWorld.GetCameraPos());
	SetPosition(_vMovingPos, _vCameraPos);
	EffectUpdate();
	return true;
}

bool Monster::CInit()
{
	if (_bSoundInit == false)
	{
		for (int i = 0; i < 5; ++i)
		{
			pSound[i] = I_Sound.Load(L"../../resource/sfx/VS_EnemyHit_v06-02.ogg");
			_blankIndexList.push_back(i);
		}
		_bSoundInit = true;
	}
	Monster::Init();
	_bAnimation = true;
	_pSprite = I_Sprite.GetPtr(L"rtMonsterA");
	Create(I_GameWorld.GetDevice(), I_GameWorld.GetDeviceImmediateContext(), L"../../data/shader/DefaultShapeMask.txt", L"../../data/bitmap1.bmp");
	Object2D::SetPosition(Vector2D(0.0f, 0.0f));
	CreateComponent<CircleComponent>();
	GetComponent<CircleComponent>()->fRadius = 10.0f;
	InitSprite();
	g_CreateMonster++;
	return true;
}

bool Monster::CFrame()
{
	Monster::Frame();
	return true;
}

bool Monster::CRender()
{
	Monster::Render();
	return true;
}

bool Monster::CRelease()
{
	if (_allockSoundIndex != -1)
	{
		pSound[_allockSoundIndex]->Stop();
		_blankIndexList.push_back(_allockSoundIndex);
	}
	Monster::Release();
	ComponentObject::CRelease();
	return true;
}

bool Monster::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	if (eventType == EventType::CollisionIn)
	{
		ComponentObject* pComponent = static_cast<ComponentObject*>(msg->_pExtraInfo);
		Monster* pMonster = dynamic_cast<Monster*>(pComponent);
		if (pMonster != nullptr)
		{
			Vector2D ToMonster = pMonster->_vMovingPos - _vMovingPos;
			float DistFrom = ToMonster.Length();
			float overlap = pMonster->GetComponent<CircleComponent>()->fRadius + GetComponent<CircleComponent>()->fRadius - DistFrom;
			if (overlap >= 0)
			{
				pMonster->SetPosition(pMonster->_vMovingPos + (ToMonster / DistFrom) * overlap, I_GameWorld.GetCameraPos());
			}
		}
	}
	return true;
}

void Monster::Damanged(int damanged)
{
	SetImmuneCounter(200);
	_blinkTimer.Start(300);
	_iHearth -= damanged;
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
	if (_iHearth <= 0 && _bDeath == false)
	{
		_bDeath = true;
		g_DeadMonster++;
		DestroyObject(GetIndex());
		auto pDead = CreateObject<DeadMonster>();
		pDead->SetPosition({ _vMovingPos }, I_GameWorld.GetCameraPos());

	}
}

void Monster::SetImmuneCounter(int counter)
{
	_immuneCounter.Start(counter);
	_bImmue = true;
}

bool Monster::IsImmune()
{
	return _bImmue;
}

bool Monster::UpdateBlink()
{
	return true;
}
