#include "Object2DComponent.h"
#include "Sprite.h"

bool Object2DComponent::CInit()
{
	return Object2D::Init();
}

bool Object2DComponent::CFrame()
{
	return Object2D::Frame();
}

bool Object2DComponent::CRender()
{
	return Object2D::Render();
}

bool Object2DComponent::CRelease()
{
	ComponentObject::CRelease();
	return Object2D::Release();
}

bool Object2DComponent::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	return true;
}

Rect Object2DComponent::convert(RECT rt)
{
	Rect tRt;
	tRt.x1 = rt.left;
	tRt.y1 = rt.top;
	tRt.w = rt.right;
	tRt.h = rt.bottom;
	return tRt;
}

bool Object2DComponent::EffectUpdate()
{
	_fEffectTimer += g_fSecondPerFrame;
	if (_fStep <= _fEffectTimer)
	{
		_fEffectTimer -= _fStep;
		_iIndex++;
	}
	if (_iIndex >= _iMaxIndex)
	{
		_iIndex = 0;
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
	//_pSprite->SetCameraSize(_vViewSize);
	//_pSprite->SetCameraPos(_vCameraPos);
	//_pSprite->SetRect(_tRect);
	//_pSprite->SetPosition(_vPos, _vCameraPos);
	//if (_bFlip == true)
	//{
	//	_pSprite->UpdateVertexBufferFlip();
	//}
	return true;
}

bool Object2DComponent::InitSprite()
{
	_fEffectTimer = 0.0f;
	RECT rt = _pSprite->_uvArray[0];
	_tRect.x1 = rt.left;
	_tRect.y1 = rt.top;
	_tRect.w = rt.right;
	_tRect.h = rt.bottom;
	_iIndex = 0;
	_fLifeTime = 1.0f;
	_fStep = _fLifeTime /
		_pSprite->_uvArray.size();
	_iMaxIndex = _pSprite->_uvArray.size();
	_pSprite->SetRect(_tRect);
	_pSprite->SetPosition(_vPos);
	_rtCollision = _pSprite->_rtCollision;
	_rtCollision.x1 = _vPos.x;
	_rtCollision.y1 = _vPos.y;
	return true;
}
