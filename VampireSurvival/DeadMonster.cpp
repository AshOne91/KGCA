#include "DeadMonster.h"
#include "Sprite.h"
#include "GameWorld.h"
#include "Sound.h"

bool DeadMonster::_bSoundInit = false;
std::vector<int> DeadMonster::_blankIndexList;
Sound* DeadMonster::pSound[5];
void DeadMonster::SetPosition(const Vector2D& vPos, const Vector2D& vCamera)
{
	Object2DComponent::SetPosition(vPos, vCamera);
	_transform.SetPostion(vPos);
	_vMovingPos = _vPos;
}

bool DeadMonster::Render()
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

bool DeadMonster::EffectUpdate()
{
	_fEffectTimer += g_fSecondPerFrame;
	if (_fStep <= _fEffectTimer)
	{
		_fEffectTimer -= _fStep;
		_iIndex++;
	}
	if (_iIndex >= _iMaxIndex)
	{
		DestroyObject(GetIndex());
		return true;
	}
	if (_bAnimation == false)
	{
		_iIndex = 0;
	}
	RECT rt = _pSprite->_uvArray[_iIndex];
	_tRect = convert(rt);

	Vector2D	vDrawSize;
	vDrawSize.x = _rtInit.w / 2.0f;
	vDrawSize.y = _rtInit.h / 2.0f;
	_rtCollision.Set(
		_vPos.x - vDrawSize.x,
		_vPos.y - vDrawSize.y,
		_rtInit.w,
		_rtInit.h);
	return true;
}

void DeadMonster::UpdateVertexBuffer()
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

bool DeadMonster::Frame()
{
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

bool DeadMonster::CInit()
{
	if (_bSoundInit == false)
	{
		for (int i = 0; i < 5; ++i)
		{
			pSound[i] = I_Sound.Load(L"../../resource/sfx/sfx_exp_short_soft6.ogg");
			_blankIndexList.push_back(i);
		}
		_bSoundInit = true;
	}
	DeadMonster::Init();
	_fLifeTime = 1.0f;
	_bAnimation = true;
	_pSprite = I_Sprite.GetPtr(L"rtMonsterDead");
	Create(I_GameWorld.GetDevice(), I_GameWorld.GetDeviceImmediateContext(), L"../../data/shader/DefaultShapeMask.txt", L"../../data/bitmap1.bmp");
	Object2D::SetPosition(Vector2D(0.0f, 0.0f));
	InitSprite();

	if (_blankIndexList.size() > 0)
	{
		_allockSoundIndex = _blankIndexList.back();
		_blankIndexList.pop_back();
		pSound[_allockSoundIndex]->Stop();
		pSound[_allockSoundIndex]->PlayEffect();
	}
	return true;
}

bool DeadMonster::CFrame()
{
	DeadMonster::Frame();
	return true;
}

bool DeadMonster::CRender()
{
	DeadMonster::Render();
	return true;
}

bool DeadMonster::CRelease()
{
	if (_allockSoundIndex != -1)
	{
		pSound[_allockSoundIndex]->Stop();
		_blankIndexList.push_back(_allockSoundIndex);
	}
	DeadMonster::Release();
	ComponentObject::CRelease();
	return true;
}

bool DeadMonster::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	return true;
}
